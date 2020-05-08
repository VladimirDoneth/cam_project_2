//
// Created by biba_bo on 5/8/20.
//
#include <stdio.h>
#include "cam_functions.h"

static void ctx_error_func (GPContext* context, const char* str, void* data) {
    fprintf(stderr, "\n*** Contexterror *** \n%s\n", str);
    fflush(stderr);
}

static void ctx_status_func(GPContext* context, const char* str, void* data) {
    fprintf(stderr, "%s\n", str);
    fflush(stderr);
}

GPContext* create_context() {
    GPContext* context;
    context = gp_context_new();
    gp_context_set_error_func(context, ctx_error_func, NULL);
    gp_context_set_status_func(context, ctx_status_func, NULL);
    return context;
}