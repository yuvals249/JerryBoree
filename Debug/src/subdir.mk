################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/HashTable.c \
../src/Jerry.c \
../src/JerryBoreeMain.c \
../src/KeyValuePair.c \
../src/LinkedList.c \
../src/MultiValueHashTable.c 

O_SRCS += \
../src/HashTable.o \
../src/Jerry.o \
../src/JerryBoreeMain.o \
../src/KeyValuePair.o \
../src/LinkedList.o \
../src/MultiValueHashTable.o 

C_DEPS += \
./src/HashTable.d \
./src/Jerry.d \
./src/JerryBoreeMain.d \
./src/KeyValuePair.d \
./src/LinkedList.d \
./src/MultiValueHashTable.d 

OBJS += \
./src/HashTable.o \
./src/Jerry.o \
./src/JerryBoreeMain.o \
./src/KeyValuePair.o \
./src/LinkedList.o \
./src/MultiValueHashTable.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/HashTable.d ./src/HashTable.o ./src/Jerry.d ./src/Jerry.o ./src/JerryBoreeMain.d ./src/JerryBoreeMain.o ./src/KeyValuePair.d ./src/KeyValuePair.o ./src/LinkedList.d ./src/LinkedList.o ./src/MultiValueHashTable.d ./src/MultiValueHashTable.o

.PHONY: clean-src

