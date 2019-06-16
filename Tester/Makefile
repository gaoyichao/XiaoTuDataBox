
INCLUDE_PATH += -I.
INCLUDE_PATH += -I../BasicData

LIB_PATH += -L../build
LD_FLAGS += ${LIB_PATH} -lBasicData -lgtest -lgtest_main -lpthread

LIB_FILES += ${OUTPUT_PATH}/libBasicData.a

TARGET += ${OUTPUT_PATH}/t_array.exe
TARGET += ${OUTPUT_PATH}/t_s_array.exe
TARGET += ${OUTPUT_PATH}/t_queue.exe
TARGET += ${OUTPUT_PATH}/t_deque.exe
TARGET += ${OUTPUT_PATH}/t_s_queue.exe
TARGET += ${OUTPUT_PATH}/t_list.exe
TARGET += ${OUTPUT_PATH}/t_binary_tree.exe

TARGET += ${OUTPUT_PATH}/t_DataArray.exe
TARGET += ${OUTPUT_PATH}/t_DataList.exe
TARGET += ${OUTPUT_PATH}/t_DataQueue.exe
TARGET += ${OUTPUT_PATH}/t_BinaryTree.exe
TARGET += ${OUTPUT_PATH}/t_RBTree.exe

all: objs ${TARGET}

${OUTPUT_PATH}/t_array.exe: t_array.o ${LIB_FILES}
	g++ t_array.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_s_array.exe: t_s_array.o ${LIB_FILES}
	g++ t_s_array.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_queue.exe: t_queue.o ${LIB_FILES}
	g++ t_queue.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_deque.exe: t_deque.o ${LIB_FILES}
	g++ t_deque.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_s_queue.exe: t_s_queue.o ${LIB_FILES}
	g++ t_s_queue.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_list.exe: t_list.o ${LIB_FILES}
	gcc t_list.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_binary_tree.exe: t_binary_tree.o ${LIB_FILES}
	gcc t_binary_tree.o ${LD_FLAGS} -o $@


${OUTPUT_PATH}/t_DataArray.exe: t_DataArray.o ${LIB_FILES}
	g++ t_DataArray.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_DataList.exe: t_DataList.o ${LIB_FILES}
	g++ t_DataList.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_BinaryTree.exe: t_BinaryTree.o ${LIB_FILES}
	g++ t_BinaryTree.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_RBTree.exe: t_RBTree.o ${LIB_FILES}
	g++ t_RBTree.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_DataQueue.exe: t_DataQueue.o ${LIB_FILES}
	g++ t_DataQueue.o ${LD_FLAGS} -o $@


-include ../build_tools/obj.mk

clean:
	@find ${DIR_PRO} -type f \
		\( -name '*.o' -o -name '*.exe' -o -name '*~' \
		-o -name '*.swo' -o -name '*.swp' -o -name '*.a' \) -print \
		| xargs rm -f


