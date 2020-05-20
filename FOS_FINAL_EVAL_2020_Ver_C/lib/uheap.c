#include <inc/lib.h>

struct Page{
	int state;
	int sizeInPages;
};
struct Page MEMORY_LIST[(USER_HEAP_MAX-USER_HEAP_START)/PAGE_SIZE];


//int RoundUp(float n) {
//    cprintf("KAKAKA\n");
//    int intNum = (int)n;
//    cprintf("HNHNHN\n");
//    if (n == (float)intNum) {
//        return intNum;
//    }
//    return intNum + 1;
//}
//==================================================================================//
//============================ REQUIRED FUNCTIONS ==================================//
//==================================================================================//
void* malloc(uint32 size)
{

	if(sys_isUHeapPlacementStrategyFIRSTFIT()==1){
		//1) FIRST FIT strategy

		int found = 1;
		int sizeInPages = size/PAGE_SIZE ;
		sizeInPages++;

		for (int i = 0; i < sizeof(MEMORY_LIST)/sizeof(MEMORY_LIST[0]); ) {
//			cprintf("------------------------ I = %d\n",i);
			if(MEMORY_LIST[i].state == 0){
				for (int j = i; j < i+sizeInPages; j++) {
//					cprintf("\n%d - State => %d\n",j, MEMORY_LIST[j].state);

					if(MEMORY_LIST[j].state == 1){
//						cprintf("%d --- NOT EMBTY! ---\n",j);
						i=j + MEMORY_LIST[j].sizeInPages;
						found = 0;
						break;
					}
//					cprintf("--- After if in internal loop ---%d\n",j);
				}
//				cprintf("--- After the internal loop ---\n");
				if(found == 1){
//					cprintf("--- EMPTY ---\n");
					MEMORY_LIST[i].sizeInPages = sizeInPages;
					MEMORY_LIST[i].state = 1;
					sys_allocateMem(i*PAGE_SIZE+USER_HEAP_START, sizeInPages);
//					cprintf("--- ALLOCATED  ---\n");
					return (void*)(uint32*)((i*PAGE_SIZE)+USER_HEAP_START);
				}
//				cprintf("--- After the if of Found ---\n");

			}
			else{
//				cprintf("--- in the Else of outer loop ---\n");
				i += MEMORY_LIST[i].sizeInPages;
			}
//			cprintf("--- After the Else of Outer loop ---\n");

		}
		return NULL;
	}
	else if(sys_isUHeapPlacementStrategyBESTFIT()==1){
		//2) BEST FIT strategy
		return NULL;
	}
	return NULL;
}

// free():
//	This function frees the allocation of the given virtual_address
//	To do this, we need to switch to the kernel, free the pages AND "EMPTY" PAGE TABLES
//	from page file and main memory then switch back to the user again.
//
//	We can use sys_freeMem(uint32 virtual_address, uint32 size); which
//		switches to the kernel mode, calls freeMem(struct Env* e, uint32 virtual_address, uint32 size) in
//		"memory_manager.c", then switch back to the user mode here
//	the freeMem function is empty, make sure to implement it.

void free(void* virtual_address)
{
	panic("\nHELLOOOOOOOOZ from free()\n");
	//TODO: [FINAL_EVAL_2020 - VER_C] - [2] USER HEAP [User Side free]
	// Write your code here, remove the panic and write your code
	panic("free() is not implemented yet...!!");

	//you should get the size of the given allocation using its address

	//refer to the documentation for details
}


//==================================================================================//
//============================== BONUS FUNCTIONS ===================================//
//==================================================================================//
//===============
// [1] realloc():
//===============

//	Attempts to resize the allocated space at "virtual_address" to "new_size" bytes,
//	possibly moving it in the heap.
//	If successful, returns the new virtual_address, in which case the old virtual_address must no longer be accessed.
//	On failure, returns a null pointer, and the old virtual_address remains valid.

//	A call with virtual_address = null is equivalent to malloc().
//	A call with new_size = zero is equivalent to free().

//  Hint: you may need to use the sys_moveMem(uint32 src_virtual_address, uint32 dst_virtual_address, uint32 size)
//		which switches to the kernel mode, calls moveMem(struct Env* e, uint32 src_virtual_address, uint32 dst_virtual_address, uint32 size)
//		in "memory_manager.c", then switch back to the user mode here
//	the moveMem function is empty, make sure to implement it.

void *realloc(void *virtual_address, uint32 new_size)
{
	panic("this function is not required...!!");
	return 0;
}


//==================================================================================//
//================================ OTHER FUNCTIONS =================================//
//==================================================================================//

void* smalloc(char *sharedVarName, uint32 size, uint8 isWritable)
{
	panic("this function is not required...!!");
	return 0;
}

void* sget(int32 ownerEnvID, char *sharedVarName)
{
	panic("this function is not required...!!");
	return 0;
}

void sfree(void* virtual_address)
{
	panic("this function is not required...!!");
}

void expand(uint32 newSize)
{
	panic("this function is not required...!!");
}
void shrink(uint32 newSize)
{
	panic("this function is not required...!!");
}

void freeHeap(void* virtual_address)
{
	panic("this function is not required...!!");
}
