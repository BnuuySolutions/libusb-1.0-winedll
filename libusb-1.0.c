#undef _WIN32
#undef __CYGWIN__
#undef _MSC_VER
#include <libusb-1.0/libusb.h>
#include <stdlib.h>
#include <stdint.h>

#if defined(__x86_64__) || defined(_M_X64)
#define WIN_ABI __attribute__((ms_abi))
#elif defined(__i386__) || defined(_M_IX86)
#define WIN_ABI __attribute__((stdcall))
#else
#define WIN_ABI
#endif

// Windows libusb callbacks use WINAPI which maps to ms_abi on x64
typedef void (WIN_ABI *win_libusb_transfer_cb_fn)(struct libusb_transfer *transfer);

struct transfer_wrapper_context {
    win_libusb_transfer_cb_fn original_callback;
    void *original_user_data;
};

// Native Unix callback invoked by Linux libusb (SysV ABI)
static void LIBUSB_CALL unix_transfer_callback(struct libusb_transfer *transfer) {
    struct transfer_wrapper_context *ctx = (struct transfer_wrapper_context *)transfer->user_data;

    // Restore original values before firing, in case the app resubmits or inspects the transfer
    win_libusb_transfer_cb_fn win_cb = ctx->original_callback;
    transfer->user_data = ctx->original_user_data;
    transfer->callback = (libusb_transfer_cb_fn)win_cb;

    free(ctx);

    // winegcc automatically handles the transition to MS ABI via the __stdcall function pointer
    if (win_cb) {
        win_cb(transfer);
    }
}

struct libusb_transfer * WIN_ABI WinLibusb_alloc_transfer(int a){return libusb_alloc_transfer(a);}
void                   WIN_ABI WinLibusb_free_transfer(struct libusb_transfer *a){
    if (a && a->callback == (libusb_transfer_cb_fn)unix_transfer_callback) {
        free(a->user_data);
    }
    libusb_free_transfer(a);
}
void                   WIN_ABI WinLibusb_close(libusb_device_handle *a){libusb_close(a);}
void                   WIN_ABI WinLibusb_free_config_descriptor(struct libusb_config_descriptor *a){libusb_free_config_descriptor(a);}
void                   WIN_ABI WinLibusb_get_config_descriptor(libusb_device *a, uint8_t b, struct libusb_config_descriptor **c){libusb_get_config_descriptor(a,b,c);}
int                    WIN_ABI WinLibusb_get_active_config_descriptor(libusb_device *a, struct libusb_config_descriptor **b){return libusb_get_active_config_descriptor(a,b);}
int                    WIN_ABI WinLibusb_get_device_descriptor(libusb_device *a, struct libusb_device_descriptor *b){return libusb_get_device_descriptor(a,b);}
void                   WIN_ABI WinLibusb_free_device_list(libusb_device **a, int b){libusb_free_device_list(a, b);}
ssize_t                WIN_ABI WinLibusb_get_device_list(libusb_context *a,libusb_device ***b){return libusb_get_device_list(a,b);}
uint8_t                WIN_ABI WinLibusb_get_bus_number(libusb_device *a){return libusb_get_bus_number(a);}
int                    WIN_ABI WinLibusb_get_port_numbers(libusb_device *a, uint8_t *b, int c){return libusb_get_port_numbers(a,b,c);}
const char*            WIN_ABI WinLibusb_error_name(int a){return libusb_error_name(a);}
int                    WIN_ABI WinLibusb_handle_events(libusb_context *a){return libusb_handle_events(a);}
int                    WIN_ABI WinLibusb_handle_events_completed(libusb_context *a, int *b){return libusb_handle_events_completed(a,b);}
int                    WIN_ABI WinLibusb_handle_events_timeout_completed(libusb_context *a, struct timeval *b, int *c){
    if (b) {
        // Windows struct timeval uses two 32-bit integers, Linux uses two 64-bit integers.
        int32_t *win_tv = (int32_t *)b;
        struct timeval linux_tv;
        linux_tv.tv_sec = win_tv[0];
        linux_tv.tv_usec = win_tv[1];
        return libusb_handle_events_timeout_completed(a, &linux_tv, c);
    }
    return libusb_handle_events_timeout_completed(a, NULL, c);
}
void                   WIN_ABI WinLibusb_exit(libusb_context *a){return libusb_exit(a);}
int                    WIN_ABI WinLibusb_init(libusb_context ** a){return libusb_init(a);}
int                    WIN_ABI WinLibusb_bulk_transfer(libusb_device_handle *a, unsigned char b, unsigned char *c, int d, int *e, unsigned int f){return libusb_bulk_transfer(a,b,c,d,e, f);}
int                    WIN_ABI WinLibusb_interrupt_transfer(libusb_device_handle *a, unsigned char b, unsigned char *c, int d, int *e, unsigned int f){return libusb_interrupt_transfer(a,b,c,d,e,f);}
int                    WIN_ABI WinLibusb_control_transfer(libusb_device_handle *a,uint8_t b, uint8_t c, uint16_t d, uint16_t e,unsigned char *f, uint16_t g, unsigned int h){return libusb_control_transfer(a,b,c, d,e,f,g,h);}
int                    WIN_ABI WinLibusb_set_interface_alt_setting(libusb_device_handle *a , int b, int c){return libusb_set_interface_alt_setting(a,b,c);}
void                   WIN_ABI WinLibusb_get_device(libusb_device_handle *a){libusb_get_device(a);}
int                    WIN_ABI WinLibusb_open(libusb_device *a, libusb_device_handle **b){return libusb_open(a,b);}
int                    WIN_ABI WinLibusb_claim_interface(libusb_device_handle *a,int b){return libusb_claim_interface(a,b);}
libusb_device_handle * WIN_ABI WinLibusb_open_device_with_vid_pid(libusb_context *a, uint16_t b, uint16_t c){return libusb_open_device_with_vid_pid(a,b,c);}
int                    WIN_ABI WinLibusb_reset_device(struct libusb_device_handle *a){return libusb_reset_device(a);}
int                    WIN_ABI WinLibusb_submit_transfer(struct libusb_transfer *a){
    if (a && a->callback && a->callback != (libusb_transfer_cb_fn)unix_transfer_callback) {
        struct transfer_wrapper_context *ctx = malloc(sizeof(struct transfer_wrapper_context));
        if (!ctx) return LIBUSB_ERROR_NO_MEM;
        
        ctx->original_callback = (win_libusb_transfer_cb_fn)a->callback;
        ctx->original_user_data = a->user_data;
        
        a->user_data = ctx;
        a->callback = (libusb_transfer_cb_fn)unix_transfer_callback;
    }
    int ret = libusb_submit_transfer(a);
    if (ret != 0 && a && a->callback == (libusb_transfer_cb_fn)unix_transfer_callback) {
        struct transfer_wrapper_context *ctx = (struct transfer_wrapper_context *)a->user_data;
        a->callback = (libusb_transfer_cb_fn)ctx->original_callback;
        a->user_data = ctx->original_user_data;
        free(ctx);
    }
    return ret;
}
int                    WIN_ABI WinLibusb_cancel_transfer(struct libusb_transfer *a){return libusb_cancel_transfer(a);}
int                    WIN_ABI WinLibusb_wrap_sys_device(libusb_context *a, intptr_t b, libusb_device_handle **c){return libusb_wrap_sys_device(a,b,c);}
int                    WIN_ABI WinLibusb_release_interface(libusb_device_handle *a,int b){return libusb_release_interface(a,b);}
int                    WIN_ABI WinLibusb_set_configuration(libusb_device_handle *a,int b){return libusb_set_configuration(a,b);}
void                   WIN_ABI WinLibusb_set_debug(libusb_context *a, int b){libusb_set_debug(a,b);}
int                    WIN_ABI WinLibusb_kernel_driver_active(libusb_device_handle *a, int b){return libusb_kernel_driver_active(a,b);}
int                    WIN_ABI WinLibusb_detach_kernel_driver(libusb_device_handle *a, int b){return libusb_detach_kernel_driver(a,b);}
int                    WIN_ABI WinLibusb_attach_kernel_driver(libusb_device_handle *a, int b){return libusb_attach_kernel_driver(a,b);}
int                    WIN_ABI WinLibusb_set_auto_detach_kernel_driver(libusb_device_handle *a, int b){return libusb_set_auto_detach_kernel_driver(a,b);}
