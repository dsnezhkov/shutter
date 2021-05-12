#pragma once
#ifndef _MGMTGUIDS_H_
#define _MGMTGUIDS_H_

#include <guiddef.h>
#include <fwpmu.h>
#include <cstdio>
#include <iostream>

typedef struct _fwpm_layer_desc_t {
    GUID guid;       /* GUID  */
    std::string msg; /* Mnemonic */
    std::string desc; /* Description */
} fwpm_layer_desc_t;

typedef struct _fwpm_sublayer_desc_t {
    GUID guid;       /* GUID  */
    const char* msg; /* Mnemonic */
    const char* desc; /* Description */
} fwpm_sublayer_desc_t;

typedef struct _fwpm_condition_desc_t {
    GUID guid;       /* GUID  */
    const char* msg; /* Mnemonic */
    const char* desc; /* Description */
} fwpm_condition_desc_t;

bool print_fwpm_layer_desc_guidance(GUID fwpm_layer_guid, fwpm_layer_desc_t* fwpm_layer_desc);
bool print_fwpm_layer_desc_guidance(std::string fwpm_layer_msg, fwpm_layer_desc_t* fwpm_layer_desc);
bool getSublayerGuidance(GUID fwpm_sublayer_guid, std::unique_ptr<fwpm_sublayer_desc_t>& fwpm_sublayer_desc);
bool getLayerGuidance(GUID fwpm_layer_guid, std::unique_ptr<fwpm_layer_desc_t>& fwpm_layer_desc);
bool getLayerGuidance(std::string fwpm_layer_msg, std::unique_ptr<fwpm_layer_desc_t>& fwpm_layer_desc);
bool print_fwpm_condition_desc_guidance(GUID fwpm_condition_guid, fwpm_condition_desc_t* fwpm_condition_desc);


#endif
