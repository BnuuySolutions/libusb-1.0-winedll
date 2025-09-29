#undef _WIN32
#undef __CYGWIN__
#undef _MSC_VER
#include <libusb-1.0/libusb.h>

void                   __cdecl WinLibusb_close(libusb_device_handle *a){libusb_close(a);}
void                   __cdecl WinLibusb_free_config_descriptor(struct libusb_config_descriptor *a){libusb_free_config_descriptor(a);}
void                   __cdecl WinLibusb_get_config_descriptor(libusb_device *a, uint8_t b, struct libusb_config_descriptor **c){libusb_get_config_descriptor(a,b,c);}
int                    __cdecl WinLibusb_get_active_config_descriptor(libusb_device *a, struct libusb_config_descriptor **b){return libusb_get_active_config_descriptor(a,b);}
int                    __cdecl WinLibusb_get_device_descriptor(libusb_device *a, struct libusb_device_descriptor *b){return libusb_get_device_descriptor(a,b);}
void                   __cdecl WinLibusb_free_device_list(libusb_device **a, int b){libusb_free_device_list(a, b);}
ssize_t                __cdecl WinLibusb_get_device_list(libusb_context *a,libusb_device ***b){return libusb_get_device_list(a,b);}
const char*            __cdecl WinLibusb_error_name(int a){return libusb_error_name(a);}
void                   __cdecl WinLibusb_exit(libusb_context *a){return libusb_exit(a);}
int                    __cdecl WinLibusb_init(libusb_context ** a){return libusb_init(a);}
int                    __cdecl WinLibusb_bulk_transfer(libusb_device_handle *a, unsigned char b, unsigned char *c, int d, int *e, unsigned int f){return libusb_bulk_transfer(a,b,c,d,e, f);}
int                    __cdecl WinLibusb_control_transfer(libusb_device_handle *a,uint8_t b, uint8_t c, uint16_t d, uint16_t e,unsigned char *f, uint16_t g, unsigned int h){return libusb_control_transfer(a,b,c, d,e,f,g,h);}
int                    __cdecl WinLibusb_set_interface_alt_setting(libusb_device_handle *a , int b, int c){return libusb_set_interface_alt_setting(a,b,c);}
void                   __cdecl WinLibusb_get_device(libusb_device_handle *a){libusb_get_device(a);}
int                    __cdecl WinLibusb_claim_interface(libusb_device_handle *a,int b){return libusb_claim_interface(a,b);}
libusb_device_handle * __cdecl WinLibusb_open_device_with_vid_pid(libusb_context *a, uint16_t b, uint16_t c){return libusb_open_device_with_vid_pid(a,b,c);}
int                    __cdecl WinLibusb_cancel_transfer(struct libusb_transfer *a){return libusb_cancel_transfer(a);}
int                    __cdecl WinLibusb_release_interface(libusb_device_handle *a,int b){return libusb_release_interface(a,b);}
int                    __cdecl WinLibusb_set_configuration(libusb_device_handle *a,int b){return libusb_set_configuration(a,b);}
void                   __cdecl WinLibusb_set_debug(libusb_context *a, int b){libusb_set_debug(a,b);}
