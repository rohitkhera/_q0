###################################################
# Base macros and flags
###################################################

CC=g++

OPENSSL_DIR=openssl-1.1.1l/install

INCLUDES=-I$(OPENSSL_DIR)/include

CFLAGS=-g $(INCLUDES)

AR=ar

SO_FLAGS=-shared

############################################
# hdrs, srcs,  objects 
############################################

HDRS=LocalSampler.h \
	FileOps.h \
	BLASTMatrix.h 


SRCS=LocalSampler.C \
	FileOps.C \
	TestMain.C \
	BLASTMatrix.C \


OBJS=LocalSampler.o \
	FileOps.o \
	TestMain.o \
	BLASTMatrix.o 


##############################################
# Targets
##############################################

SHARED_OBJ=libsampler.so

TEST=sampler_test

DOUT=dout

TARGETS=$(SHARED_OBJ) $(TEST) $(DOUT)

all:
	make $(TARGETS)


$(TARGET): $(SHARED_OBJ)


$(SHARED_OBJ): $(OBJS)
	$(CC) $(SO_FLAGS) $(OBJS) -o $(SHARED_OBJ)


$(TEST): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TEST) -L./ -lsampler

$(DOUT): WriteBin.o
	$(CC) $(CFLAGS) $(LDFLAGS) WriteBin.o -o $(DOUT)

clean:
	@rm -rf *.o $(TARGETS)

##############################################
# Suffix Rules
##############################################

.c.o:
	$(CC) -c $(CFLAGS) $<

.C.o:
	$(CC) -c $(CFLAGS) $<







