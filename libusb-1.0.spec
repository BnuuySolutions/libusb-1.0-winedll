@ cdecl libusb_alloc_transfer(long)                                   WinLibusb_alloc_transfer
@ cdecl libusb_free_transfer(ptr)                                     WinLibusb_free_transfer
@ cdecl libusb_close(ptr)                                             WinLibusb_close
@ cdecl libusb_free_config_descriptor(ptr ptr)                        WinLibusb_free_config_descriptor
@ cdecl libusb_get_config_descriptor(ptr ptr ptr long)                WinLibusb_get_config_descriptor
@ cdecl libusb_get_active_config_descriptor(ptr ptr)                  WinLibusb_get_active_config_descriptor
@ cdecl libusb_get_device_descriptor(ptr ptr)                         WinLibusb_get_device_descriptor
@ cdecl libusb_free_device_list(ptr long)                             WinLibusb_free_device_list
@ cdecl libusb_get_device_list(ptr ptr)                               WinLibusb_get_device_list
@ cdecl libusb_get_bus_number(ptr)                                    WinLibusb_get_bus_number
@ cdecl libusb_get_port_numbers(ptr ptr long)                         WinLibusb_get_port_numbers
@ cdecl libusb_get_device_speed(ptr)                                  WinLibusb_get_device_speed
@ cdecl libusb_error_name(ptr)                                        WinLibusb_error_name
@ cdecl libusb_handle_events(ptr)                                     WinLibusb_handle_events
@ cdecl libusb_handle_events_completed(ptr ptr)                       WinLibusb_handle_events_completed
@ cdecl libusb_handle_events_timeout_completed(ptr ptr ptr)           WinLibusb_handle_events_timeout_completed
@ cdecl libusb_exit(ptr)                                              WinLibusb_exit
@ cdecl libusb_init(ptr)                                              WinLibusb_init
@ cdecl libusb_bulk_transfer(ptr ptr ptr long ptr long)               WinLibusb_bulk_transfer
@ cdecl libusb_interrupt_transfer(ptr ptr ptr long ptr long)          WinLibusb_interrupt_transfer
@ cdecl libusb_control_transfer(ptr long long long long ptr long ptr) WinLibusb_control_transfer
@ cdecl libusb_set_interface_alt_setting(ptr long long)               WinLibusb_set_interface_alt_setting
@ cdecl libusb_get_device(ptr)                                        WinLibusb_get_device
@ cdecl libusb_open(ptr ptr)                                          WinLibusb_open
@ cdecl libusb_claim_interface(ptr long)                              WinLibusb_claim_interface
@ cdecl libusb_open_device_with_vid_pid(ptr long long)                WinLibusb_open_device_with_vid_pid
@ cdecl libusb_reset_device(ptr)                                      WinLibusb_reset_device
@ cdecl libusb_submit_transfer(ptr)                                   WinLibusb_submit_transfer
@ cdecl libusb_cancel_transfer(ptr)                                   WinLibusb_cancel_transfer
@ cdecl libusb_wrap_sys_device(ptr ptr ptr)                           WinLibusb_wrap_sys_device
@ cdecl libusb_release_interface(ptr long)                            WinLibusb_release_interface
@ cdecl libusb_set_configuration(ptr long)                            WinLibusb_set_configuration
@ cdecl libusb_set_debug(ptr long)                                    WinLibusb_set_debug
@ cdecl libusb_kernel_driver_active(ptr ptr)                          WinLibusb_kernel_driver_active
@ cdecl libusb_detach_kernel_driver(ptr long)                         WinLibusb_detach_kernel_driver
@ cdecl libusb_attach_kernel_driver(ptr long)                         WinLibusb_attach_kernel_driver
@ cdecl libusb_set_auto_detach_kernel_driver(ptr long)                WinLibusb_set_auto_detach_kernel_driver
@ cdecl libusb_get_string_descriptor_ascii(ptr long ptr long)          WinLibusb_get_string_descriptor_ascii
@ cdecl libusb_ref_device(ptr)                                         WinLibusb_ref_device
@ cdecl libusb_unref_device(ptr)                                       WinLibusb_unref_device
@ cdecl libusb_strerror(long)                                          WinLibusb_strerror
@ cdecl libusb_get_configuration(ptr ptr)                              WinLibusb_get_configuration
@ cdecl libusb_clear_halt(ptr long)                                    WinLibusb_clear_halt
@ varargs libusb_set_option(ptr long)                                  WinLibusb_set_option

