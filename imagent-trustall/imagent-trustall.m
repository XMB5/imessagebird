//you must disable SIP/`csrutil disable` for this to work
//clang -o imagent-trustall.dylib -dynamiclib imagent-trustall.m -framework Foundation

// _IMDAuditTokenTaskHasEntitlement(&param_5,&cf_com.apple.imagent.av);
// -> implemented in IMFoundation

#include <dlfcn.h>
#include <stdio.h>
#import <Foundation/Foundation.h>
#include <mach-o/dyld.h>
#include <mach-o/nlist.h>
#include <mach-o/dyld.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

// https://stackoverflow.com/a/21855885
// Adapted from:
// https://github.com/0xced/iOS-Artwork-Extractor/blob/master/Classes/FindSymbol.c
// Adapted from MoreAddrToSym / GetFunctionName()
// http://www.opensource.apple.com/source/openmpi/openmpi-8/openmpi/opal/mca/backtrace/darwin/MoreBacktrace/MoreDebugging/MoreAddrToSym.c
static void* FindSymbol(const struct mach_header *img, const char *symbol)
{
    if ((img == NULL) || (symbol == NULL))
        return NULL;

    // only 64bit supported
#if defined (__LP64__)

    if(img->magic != MH_MAGIC_64)
        // we currently only support Intel 64bit
        return NULL;

    struct mach_header_64 *image = (struct mach_header_64*) img;

    struct segment_command_64 *seg_linkedit = NULL;
    struct segment_command_64 *seg_text = NULL;
    struct symtab_command *symtab = NULL;
    unsigned int index;

    struct load_command *cmd = (struct load_command*)(image + 1);

    for (index = 0; index < image->ncmds; index += 1, cmd = (struct load_command*)((char*)cmd + cmd->cmdsize))
    {
        switch(cmd->cmd)
        {
            case LC_SEGMENT_64: {
                struct segment_command_64* segcmd = (struct segment_command_64*)cmd;
                if (!strcmp(segcmd->segname, SEG_TEXT))
                    seg_text = segcmd;
                else if (!strcmp(segcmd->segname, SEG_LINKEDIT))
                    seg_linkedit = segcmd;
                break;
            }

            case LC_SYMTAB:
                symtab = (struct symtab_command*)cmd;
                break;

            default:
                break;
        }
    }

    if ((seg_text == NULL) || (seg_linkedit == NULL) || (symtab == NULL))
        return NULL;

    unsigned long vm_slide = (unsigned long)image - (unsigned long)seg_text->vmaddr;
    unsigned long file_slide = ((unsigned long)seg_linkedit->vmaddr - (unsigned long)seg_text->vmaddr) - seg_linkedit->fileoff;
    struct nlist_64 *symbase = (struct nlist_64*)((unsigned long)image + (symtab->symoff + file_slide));
    char *strings = (char*)((unsigned long)image + (symtab->stroff + file_slide));
    struct nlist_64 *sym;

    for (index = 0, sym = symbase; index < symtab->nsyms; index += 1, sym += 1)
    {
        if (sym->n_un.n_strx != 0 && !strcmp(symbol, strings + sym->n_un.n_strx))
        {
            unsigned long address = vm_slide + sym->n_value;
            if (sym->n_desc & N_ARM_THUMB_DEF)
                return (void*)(address | 1);
            else
                return (void*)(address);
        }
    }
#endif

    return NULL;
}

static uint8_t functionReplacementAsm[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3 };
/*
 0:  b8 01 00 00 00          mov    eax,0x1
 5:  c3                      ret
 */

static const char* IMFOUNDATION_LIB_PATH = "/System/Library/PrivateFrameworks/IMFoundation.framework/Versions/A/IMFoundation";
static const char* FUNCTION_NAME = "_IMDAuditTokenTaskHasEntitlement";

static int checkDlErr() {
    const char* err = dlerror();
    if (err != NULL) {
        NSLog(@"trustall dl error: %s", err);
        return 1;
    }
    return 0;
}

__attribute__((constructor))
static void ctor() {
    NSLog(@"trustall dylib loaded");
    dlopen(IMFOUNDATION_LIB_PATH, RTLD_LAZY);
    if (checkDlErr()) return;
    
    //https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/dyld.3.html
    const struct mach_header* machHeader = NULL;
    int numDls = _dyld_image_count();
    for (int i = 0; i < numDls; i++) {
        const char* name = _dyld_get_image_name(i);
        if (strcmp(name, IMFOUNDATION_LIB_PATH) == 0) {
            machHeader = _dyld_get_image_header(i);
            break;
        }
    }
    if (machHeader == NULL) {
        NSLog(@"unable to find dynamic library when iterating");
        return;
    }
    
    //the symbol isn't exported, so dlsym() doesn't find it
    uint8_t* functionLoc = (uint8_t*) FindSymbol(machHeader, FUNCTION_NAME);
    if (functionLoc == NULL) {
        NSLog(@"trustall could not find location of %s", FUNCTION_NAME);
        return;
    } else {
        NSLog(@"trustall %s location %p", FUNCTION_NAME, functionLoc);
    }
    
    //https://stackoverflow.com/questions/20381812/mprotect-always-returns-invalid-arguments
    size_t pageSize = sysconf(_SC_PAGESIZE);
    uintptr_t start = (uintptr_t)functionLoc;
    uintptr_t end = start + 1;
    uintptr_t pageStart = start & -pageSize;
    mprotect((void *)pageStart, end - pageStart, PROT_READ | PROT_WRITE | PROT_EXEC);

    for (int i = 0; i < sizeof(functionReplacementAsm); i++) {
        *(functionLoc + i) = functionReplacementAsm[i];
    }
}
