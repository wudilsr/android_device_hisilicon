ifeq ($(CFG_HI_PQ_V1_0),y)
PQ_DIR := pq/pq_v1_0
endif

ifeq ($(CFG_HI_PQ_V2_0),y)
PQ_DIR := pq/pq_v2_0
endif

ifeq ($(CFG_HI_PQ_V3_0),y)
PQ_DIR := pq/pq_v2_0
endif

LOCAL_SRC_FILES += $(PQ_DIR)/mpi_pq.c
LOCAL_SRC_FILES += $(PQ_DIR)/unf_pq.c

ifeq ($(CFG_HI_PQ_V1_0),y)
LOCAL_SRC_FILES += $(PQ_DIR)/mpi_pq_tran.c
endif

