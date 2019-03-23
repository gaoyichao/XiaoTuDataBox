
INCLUDE_PATH += -I.
INCLUDE_PATH += -I../BasicData

LIB_PATH += -L../build
LD_FLAGS += ${LIB_PATH} -lBasicData -lgtest -lgtest_main -lpthread

TARGET += ${OUTPUT_PATH}/t_array.exe
TARGET += ${OUTPUT_PATH}/t_s_array.exe
TARGET += ${OUTPUT_PATH}/t_DataArray.exe
TARGET += ${OUTPUT_PATH}/t_list.exe

all: ${TARGET}

${OUTPUT_PATH}/t_array.exe: objs
	g++ t_array.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_s_array.exe: objs
	g++ t_s_array.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_DataArray.exe: objs
	g++ t_DataArray.o ${LD_FLAGS} -o $@

${OUTPUT_PATH}/t_list.exe: objs
	g++ t_list.o ${LD_FLAGS} -o $@

-include ../build_tools/obj.mk

clean:
	@find ${DIR_PRO} -type f \
		\( -name '*.o' -o -name '*.exe' -o -name '*~' \
		-o -name '*.swo' -o -name '*.swp' -o -name '*.a' \) -print \
		| xargs rm -f


