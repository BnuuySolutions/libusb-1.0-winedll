#include <stdio.h>
#undef _WIN32
#undef __CYGWIN__
#undef _MSC_VER
#include <libusb-1.0/libusb.h>
#include <hidapi/hidapi.h>

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

const uint8_t INPUT_REPORT_CRC32_SEED = 0xa1;
const uint8_t OUTPUT_REPORT_CRC32_SEED = 0xa2;
const uint8_t FEATURE_REPORT_CRC32_SEED = 0xa3;

const uint32_t CRC_POLYNOMIAL = 0xedb88320;
static uint32_t
crc32_le(uint32_t crc, uint8_t const *p, size_t len)
{
	int i;
	crc ^= 0xffffffff;
	while (len--) {
		crc ^= *p++;
		for (i = 0; i < 8; i++)
			crc = (crc >> 1) ^ ((crc & 1) ? CRC_POLYNOMIAL : 0);
	}
	return crc ^ 0xffffffff;
}

// Hidapi
size_t numberOfReads = 0;
hid_device *           __cdecl WinHid_open(unsigned short a, unsigned short b, const wchar_t *c){return hid_open(a,b,c);}
int                    __cdecl WinHid_write(hid_device *a, const unsigned char *b, size_t c){return hid_write(a,b,c);}
int                    __cdecl WinHid_read_timeout(hid_device *a, unsigned char *b, size_t c, int d){
    numberOfReads++;
    int e = hid_read_timeout(a,b,c,d);

    if (e == 78 && numberOfReads > 30)
    {
        b[33] = 0x01;
    }

    fprintf(stderr, "read\n");
    for (int i = 0; i < d; i++) {
        fprintf(stderr, "%02x ", b[i]);
    }
    fprintf(stderr, "\n");

    return e;
}
int                    __cdecl WinHid_read(hid_device *a, unsigned char *b, size_t c){
    numberOfReads++;
    int d = hid_read(a,b,c);

    if (d == 78 && numberOfReads > 30)
    {
        b[53] = 0x01;
        uint32_t crc = crc32_le(0, &INPUT_REPORT_CRC32_SEED, 1);
	    crc = crc32_le(crc, (uint8_t *)b, 78 - 4);

        *(uint32_t*)(b + 74) = crc;
    }

    return d;
}
size_t numberOfFeatureReports = 0;
int                    __cdecl WinHid_send_feature_report(hid_device *a, const unsigned char *b, size_t c){
    numberOfFeatureReports++;

    if (numberOfFeatureReports > 30)
    {
        return 0;
    }

    fprintf(stderr, "Sending feature report\n");
    for (int i = 0; i < c; i++) {
        fprintf(stderr, "%02x ", b[i]);
    }
    fprintf(stderr, "\n");

    return hid_send_feature_report(a,b,c);
}
int                    __cdecl WinHid_get_feature_report(hid_device *a, unsigned char *b, size_t c){
    numberOfFeatureReports++;

    if (numberOfFeatureReports > 30)
    {
        return 0;
    }

    fprintf(stderr, "Getting feature report\n");
    for (int i = 0; i < c; i++) {
        fprintf(stderr, "%02x ", b[i]);
    }
    fprintf(stderr, "\n");
    int d = hid_get_feature_report(a,b,c);
    if (d < 0) {
        fprintf(stderr, "Error getting feature report\n");
    }

    fprintf(stderr, "Got feature report\n");
    for (int i = 0; i < d; i++) {
        fprintf(stderr, "%02x ", b[i]);
    }
    fprintf(stderr, "\n");

    return d;
}
void                   __cdecl WinHid_close(hid_device *a){hid_close(a);}
