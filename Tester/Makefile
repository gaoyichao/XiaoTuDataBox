
INCLUDE_PATH += -I.
INCLUDE_PATH += -I../BasicData

LIB_PATH += -L../build
LD_FLAGS += ${LIB_PATH} -lBasicData -lgtest -lgtest_main -lpthread

TARGET += ${OUTPUT_PATH}/t_array.exe
TARGET += ${OUTPUT_PATH}/t_s_array.exe
TARGET += ${OUTPUT_PATH}/t_queue.exe
TARGET += ${OUTPUT_PATH}/t_s_queue.exe
TARGET += ${OUTPUT_PATH}/t_list.exe

TARGET += ${OUTPUT_PATH}/t_DataArray.exe
TARGET += ${OUTPUT_PATH}/t_DataList.exe

all: objs ${TARGET}

${OUTPUT_PATH}/t_array.exe: t_array.o
	g++ t_array.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_s_array.exe: t_s_array.o 
	g++ t_s_array.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_queue.exe: t_queue.o
	g++ t_queue.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_s_queue.exe: t_s_queue.o
	g++ t_s_queue.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_list.exe: t_list.o
	gcc t_list.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_DataArray.exe: t_DataArray.o
	g++ t_DataArray.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_DataList.exe: t_DataList.o
	g++ t_DataList.o ${LD_FLAGS} -o $@

-include ../build_tools/obj.mk

clean:
	@find ${DIR_PRO} -type f \
		\( -name '*.o' -o -name '*.exe' -o -name '*~' \
		-o -name '*.swo' -o -name '*.swp' -o -name '*.a' \) -print \
		| xargs rm -f


