.POSIX:

CONFIGFILE = config.mk
include $(CONFIGFILE)

OS = linux
# Linux:   linux
# Mac OS:  macos
# Windows: windows
include mk/$(OS).mk


LIB_MAJOR = 1
LIB_MINOR = 1
LIB_VERSION = $(LIB_MAJOR).$(LIB_MINOR)
LIB_NAME = j2


OBJ =\
	libj2_j2u_add_j2u.o\
	libj2_j2u_add_j2u_overflow.o\
	libj2_j2u_add_j2u_to_j2u.o\
	libj2_j2u_add_j2u_to_j2u_overflow.o\
	libj2_j2u_add_ju.o\
	libj2_j2u_add_ju_overflow.o\
	libj2_j2u_add_ju_to_j2u.o\
	libj2_j2u_add_ju_to_j2u_overflow.o\
	libj2_j2u_and_j2u.o\
	libj2_j2u_and_j2u_to_j2u.o\
	libj2_j2u_and_ju.o\
	libj2_j2u_and_ju_to_j2u.o\
	libj2_j2u_cmp_j2u.o\
	libj2_j2u_cmp_ju.o\
	libj2_j2u_div_j2u.o\
	libj2_j2u_div_j2u_return.o\
	libj2_j2u_div_j2u_to_j2u.o\
	libj2_j2u_div_ju.o\
	libj2_j2u_div_ju_return.o\
	libj2_j2u_div_ju_to_j2u.o\
	libj2_j2u_divmod_j2u.o\
	libj2_j2u_divmod_j2u_to_j2u.o\
	libj2_j2u_divmod_j2u_to_j2u_j2u.o\
	libj2_j2u_divmod_ju.o\
	libj2_j2u_divmod_ju_to_j2u.o\
	libj2_j2u_divmod_ju_to_j2u_j2u.o\
	libj2_j2u_eq_j2u.o\
	libj2_j2u_eq_ju.o\
	libj2_j2u_ge_j2u.o\
	libj2_j2u_ge_ju.o\
	libj2_j2u_gt_j2u.o\
	libj2_j2u_gt_ju.o\
	libj2_j2u_if_j2u.o\
	libj2_j2u_if_j2u_to_j2u.o\
	libj2_j2u_if_ju.o\
	libj2_j2u_if_ju_to_j2u.o\
	libj2_j2u_imply_j2u.o\
	libj2_j2u_imply_j2u_to_j2u.o\
	libj2_j2u_imply_ju.o\
	libj2_j2u_imply_ju_to_j2u.o\
	libj2_j2u_is_max.o\
	libj2_j2u_is_min.o\
	libj2_j2u_is_positive.o\
	libj2_j2u_is_zero.o\
	libj2_j2u_le_j2u.o\
	libj2_j2u_le_ju.o\
	libj2_j2u_lrot.o\
	libj2_j2u_lrot_to_j2u.o\
	libj2_j2u_lsh.o\
	libj2_j2u_lsh_overflow.o\
	libj2_j2u_lsh_to_j2u.o\
	libj2_j2u_lsh_to_j2u_overflow.o\
	libj2_j2u_lt_j2u.o\
	libj2_j2u_lt_ju.o\
	libj2_j2u_max.o\
	libj2_j2u_max_j2u.o\
	libj2_j2u_max_j2u_to_j2u.o\
	libj2_j2u_max_ju.o\
	libj2_j2u_max_ju_to_j2u.o\
	libj2_j2u_min.o\
	libj2_j2u_min_j2u.o\
	libj2_j2u_min_j2u_to_j2u.o\
	libj2_j2u_min_ju.o\
	libj2_j2u_min_ju_to_j2u.o\
	libj2_j2u_mod_j2u.o\
	libj2_j2u_mod_j2u_to_j2u.o\
	libj2_j2u_mod_ju.o\
	libj2_j2u_mod_ju_to_j2u.o\
	libj2_j2u_mul_j2u.o\
	libj2_j2u_mul_j2u_destructive.o\
	libj2_j2u_mul_j2u_overflow.o\
	libj2_j2u_mul_j2u_overflow_destructive.o\
	libj2_j2u_mul_j2u_to_j2u.o\
	libj2_j2u_mul_j2u_to_j2u_overflow.o\
	libj2_j2u_mul_ju.o\
	libj2_j2u_mul_ju_overflow.o\
	libj2_j2u_mul_ju_to_j2u.o\
	libj2_j2u_mul_ju_to_j2u_overflow.o\
	libj2_j2u_nand_j2u.o\
	libj2_j2u_nand_j2u_to_j2u.o\
	libj2_j2u_nand_ju.o\
	libj2_j2u_nand_ju_to_j2u.o\
	libj2_j2u_ne_j2u.o\
	libj2_j2u_ne_ju.o\
	libj2_j2u_nif_j2u.o\
	libj2_j2u_nif_j2u_to_j2u.o\
	libj2_j2u_nif_ju.o\
	libj2_j2u_nif_ju_to_j2u.o\
	libj2_j2u_nimply_j2u.o\
	libj2_j2u_nimply_j2u_to_j2u.o\
	libj2_j2u_nimply_ju.o\
	libj2_j2u_nimply_ju_to_j2u.o\
	libj2_j2u_nor_j2u.o\
	libj2_j2u_nor_j2u_to_j2u.o\
	libj2_j2u_nor_ju.o\
	libj2_j2u_nor_ju_to_j2u.o\
	libj2_j2u_or_j2u.o\
	libj2_j2u_or_j2u_to_j2u.o\
	libj2_j2u_or_ju.o\
	libj2_j2u_or_ju_to_j2u.o\
	libj2_j2u_rdiv_j2u.o\
	libj2_j2u_rdivmod_j2u.o\
	libj2_j2u_rdivmod_j2u_to_j2u.o\
	libj2_j2u_rmod_j2u.o\
	libj2_j2u_rrot.o\
	libj2_j2u_rrot_to_j2u.o\
	libj2_j2u_rsh.o\
	libj2_j2u_rsh_to_j2u.o\
	libj2_j2u_rsh_to_j2u_underflow.o\
	libj2_j2u_rsh_underflow.o\
	libj2_j2u_rsub_j2u.o\
	libj2_j2u_rsub_j2u_overflow.o\
	libj2_j2u_rsub_ju.o\
	libj2_j2u_rsub_ju_overflow.o\
	libj2_j2u_sub_j2u.o\
	libj2_j2u_sub_j2u_overflow.o\
	libj2_j2u_sub_j2u_to_j2u.o\
	libj2_j2u_sub_j2u_to_j2u_overflow.o\
	libj2_j2u_sub_ju.o\
	libj2_j2u_sub_ju_overflow.o\
	libj2_j2u_sub_ju_to_j2u.o\
	libj2_j2u_sub_ju_to_j2u_overflow.o\
	libj2_j2u_test_bit.o\
	libj2_j2u_test_high_ju.o\
	libj2_j2u_test_j2u.o\
	libj2_j2u_test_ju.o\
	libj2_j2u_xnor_j2u.o\
	libj2_j2u_xnor_j2u_to_j2u.o\
	libj2_j2u_xnor_ju.o\
	libj2_j2u_xnor_ju_to_j2u.o\
	libj2_j2u_xor_j2u.o\
	libj2_j2u_xor_j2u_to_j2u.o\
	libj2_j2u_xor_ju.o\
	libj2_j2u_xor_ju_to_j2u.o\
	libj2_j2u_zero.o\
	libj2_ju_add_j2u_to_j2u.o\
	libj2_ju_add_j2u_to_j2u_overflow.o\
	libj2_ju_add_ju_to_j2u.o\
	libj2_ju_and_j2u_to_j2u.o\
	libj2_ju_cmp_j2u.o\
	libj2_ju_eq_j2u.o\
	libj2_ju_ge_j2u.o\
	libj2_ju_gt_j2u.o\
	libj2_ju_if_j2u_to_j2u.o\
	libj2_ju_imply_j2u_to_j2u.o\
	libj2_ju_le_j2u.o\
	libj2_ju_lrot_to_j2u.o\
	libj2_ju_lsh_to_j2u.o\
	libj2_ju_lsh_to_j2u_overflow.o\
	libj2_ju_lt_j2u.o\
	libj2_ju_mul_j2u_to_j2u.o\
	libj2_ju_mul_j2u_to_j2u_overflow.o\
	libj2_ju_mul_ju_to_j2u.o\
	libj2_ju_nand_j2u_to_j2u.o\
	libj2_ju_ne_j2u.o\
	libj2_ju_nif_j2u_to_j2u.o\
	libj2_ju_nimply_j2u_to_j2u.o\
	libj2_ju_nor_j2u_to_j2u.o\
	libj2_ju_or_j2u_to_j2u.o\
	libj2_ju_rrot_to_j2u.o\
	libj2_ju_rsh_to_j2u.o\
	libj2_ju_rsh_to_j2u_underflow.o\
	libj2_ju_sub_j2u_to_j2u.o\
	libj2_ju_sub_j2u_to_j2u_overflow.o\
	libj2_ju_sub_ju_to_j2u.o\
	libj2_ju_sub_ju_to_j2u_overflow.o\
	libj2_ju_to_j2u.o\
	libj2_ju_xnor_j2u_to_j2u.o\
	libj2_ju_xor_j2u_to_j2u.o\
	libj2_max_j2u.o\
	libj2_max_j2u_return.o\
	libj2_max_j2u_to_j2u.o\
	libj2_min_j2u.o\
	libj2_min_j2u_return.o\
	libj2_min_j2u_to_j2u.o\
	libj2_minus_j2u.o\
	libj2_minus_j2u_to_j2u.o\
	libj2_not_j2u.o\
	libj2_not_j2u_to_j2u.o\
	libj2_not_ju_to_j2u.o\
	libj2_sgn_j2u.o\
	libj2_vmax_j2u.o\
	libj2_vmax_j2u_return.o\
	libj2_vmax_j2u_to_j2u.o\
	libj2_vmin_j2u.o\
	libj2_vmin_j2u_return.o\
	libj2_vmin_j2u_to_j2u.o\
	libj2_j2u_and_bit_to_j2u.o\
	libj2_j2u_and_bit.o\
	libj2_j2u_or_bit_to_j2u.o\
	libj2_j2u_or_bit.o\
	libj2_j2u_xor_bit_to_j2u.o\
	libj2_j2u_xor_bit.o\
	libj2_j2u_if_bit_to_j2u.o\
	libj2_j2u_if_bit.o\
	libj2_j2u_imply_bit_to_j2u.o\
	libj2_j2u_imply_bit.o\
	libj2_j2u_nand_bit_to_j2u.o\
	libj2_j2u_nand_bit.o\
	libj2_j2u_nor_bit_to_j2u.o\
	libj2_j2u_nor_bit.o\
	libj2_j2u_xnor_bit_to_j2u.o\
	libj2_j2u_xnor_bit.o\
	libj2_j2u_nif_bit_to_j2u.o\
	libj2_j2u_nif_bit.o\
	libj2_j2u_nimply_bit_to_j2u.o\
	libj2_j2u_nimply_bit.o\
	libj2_clz_j2u.o\
	libj2_clo_j2u.o\
	libj2_ctz_j2u.o\
	libj2_cto_j2u.o\
	libj2_co_j2u.o\
	libj2_cz_j2u.o\
	libj2_ffs_j2u.o\
	libj2_ffc_j2u.o\
	libj2_fls_j2u.o\
	libj2_flc_j2u.o\
	libj2_parity_j2u.o\
	libj2_kfs_j2u.o\
	libj2_kfs_j2u_to_j2u.o\
	libj2_kls_j2u.o\
	libj2_kls_j2u_to_j2u.o\
	libj2_cfs_j2u.o\
	libj2_cfs_j2u_to_j2u.o\
	libj2_cls_j2u.o\
	libj2_cls_j2u_to_j2u.o\
	libj2_sfc_j2u.o\
	libj2_sfc_j2u_to_j2u.o\
	libj2_slc_j2u.o\
	libj2_slc_j2u_to_j2u.o\
	libj2_j2u_has_j2u.o\
	libj2_j2u_has_ju.o\
	libj2_j2u_has_high_ju.o\
	libj2_j2u_lsh_overflow_p.o\
	libj2_ju_lsh_overflow_p.o\
	libj2_j2u_rsh_underflow_p.o\
	libj2_ju_rsh_underflow_p.o\
	libj2_j2u_add_ju_overflow_p.o\
	libj2_ju_add_j2u_overflow_p.o\
	libj2_j2u_add_j2u_overflow_p.o\
	libj2_j2u_sub_ju_overflow_p.o\
	libj2_ju_sub_j2u_overflow_p.o\
	libj2_ju_sub_ju_overflow_p.o\
	libj2_j2u_sub_j2u_overflow_p.o\
	libj2_j2u_rsub_j2u_overflow_p.o\
	libj2_j2u_rsub_ju_overflow_p.o\
	libj2_j2u_mul_j2u_overflow_p_quick.o\
	libj2_j2u_mul_ju_overflow_p_quick.o\
	libj2_ju_mul_j2u_overflow_p_quick.o\
	libj2_j2u_mul_j2u_overflow_p.o\
	libj2_j2u_mul_ju_overflow_p.o\
	libj2_ju_mul_j2u_overflow_p.o\
	libj2_j2u_mul_j2u_to_j2u_overflow_p.o\
	libj2_j2u_mul_ju_to_j2u_overflow_p.o\
	libj2_ju_mul_j2u_to_j2u_overflow_p.o\
	libj2_j2u_div_j2u_underflow.o\
	libj2_j2u_div_j2u_to_j2u_underflow.o\
	libj2_j2u_rdiv_j2u_underflow.o\
	libj2_j2u_div_ju_underflow.o\
	libj2_j2u_div_ju_to_j2u_underflow.o\
	libj2_j2u_sat_lsh.o\
	libj2_j2u_sat_lsh_to_j2u.o\
	libj2_ju_sat_lsh_to_j2u.o\
	libj2_j2u_sat_add_ju.o\
	libj2_j2u_sat_add_ju_to_j2u.o\
	libj2_ju_sat_add_j2u_to_j2u.o\
	libj2_j2u_sat_add_j2u.o\
	libj2_j2u_sat_add_j2u_to_j2u.o\
	libj2_j2u_sat_sub_ju.o\
	libj2_j2u_sat_sub_ju_to_j2u.o\
	libj2_ju_sat_sub_ju_to_j2u.o\
	libj2_j2u_sat_sub_j2u.o\
	libj2_j2u_sat_sub_j2u_to_j2u.o\
	libj2_ju_sat_sub_j2u_to_j2u.o\
	libj2_j2u_sat_rsub_j2u.o\
	libj2_j2u_sat_rsub_ju.o\
	libj2_j2u_sat_mul_ju.o\
	libj2_j2u_sat_mul_ju_to_j2u.o\
	libj2_ju_sat_mul_j2u_to_j2u.o\
	libj2_j2u_sat_mul_j2u_destructive.o\
	libj2_j2u_sat_mul_j2u.o\
	libj2_j2u_sat_mul_j2u_to_j2u.o\
	libj2_j2u_to_str.o\
	libj2_j2i_to_str.o\
	libj2_str_to_j2u.o\
	libj2_str_to_j2u_sign.o\
	libj2_str_to_j2i.o\
	libj2_j2i_is_zero.o\
	libj2_j2i_zero.o\
	libj2_j2i_is_max.o\
	libj2_j2i_max.o\
	libj2_j2i_is_min.o\
	libj2_j2i_min.o\
	libj2_ju_to_j2i.o\
	libj2_ji_to_j2i.o\
	libj2_j2u_to_j2i.o\
	libj2_j2i_to_j2u.o\
	libj2_j2i_is_positive.o\
	libj2_j2i_is_negative.o\
	libj2_sgn_j2i.o\
	libj2_j2i_eq_j2i.o\
	libj2_j2i_eq_ji.o\
	libj2_j2i_ge_j2i.o\
	libj2_j2i_ge_ji.o\
	libj2_j2i_gt_j2i.o\
	libj2_j2i_gt_ji.o\
	libj2_j2i_le_j2i.o\
	libj2_j2i_le_ji.o\
	libj2_j2i_lt_j2i.o\
	libj2_j2i_lt_ji.o\
	libj2_j2i_ne_j2i.o\
	libj2_j2i_ne_ji.o\
	libj2_ji_eq_j2i.o\
	libj2_ji_ge_j2i.o\
	libj2_ji_gt_j2i.o\
	libj2_ji_le_j2i.o\
	libj2_ji_lt_j2i.o\
	libj2_ji_ne_j2i.o\
	libj2_j2u_eq_j2i.o\
	libj2_j2u_eq_ji.o\
	libj2_j2u_ge_j2i.o\
	libj2_j2u_ge_ji.o\
	libj2_j2u_gt_j2i.o\
	libj2_j2u_gt_ji.o\
	libj2_j2u_le_j2i.o\
	libj2_j2u_le_ji.o\
	libj2_j2u_lt_j2i.o\
	libj2_j2u_lt_ji.o\
	libj2_j2u_ne_j2i.o\
	libj2_j2u_ne_ji.o\
	libj2_ju_eq_j2i.o\
	libj2_ju_ge_j2i.o\
	libj2_ju_gt_j2i.o\
	libj2_ju_le_j2i.o\
	libj2_ju_lt_j2i.o\
	libj2_ju_ne_j2i.o\
	libj2_j2i_eq_j2u.o\
	libj2_j2i_eq_ju.o\
	libj2_j2i_ge_j2u.o\
	libj2_j2i_ge_ju.o\
	libj2_j2i_gt_j2u.o\
	libj2_j2i_gt_ju.o\
	libj2_j2i_le_j2u.o\
	libj2_j2i_le_ju.o\
	libj2_j2i_lt_j2u.o\
	libj2_j2i_lt_ju.o\
	libj2_j2i_ne_j2u.o\
	libj2_j2i_ne_ju.o\
	libj2_ji_eq_j2u.o\
	libj2_ji_ge_j2u.o\
	libj2_ji_gt_j2u.o\
	libj2_ji_le_j2u.o\
	libj2_ji_lt_j2u.o\
	libj2_ji_ne_j2u.o\
	libj2_ji_cmp_j2i.o\
	libj2_j2i_cmp_ji.o\
	libj2_j2i_cmp_j2i.o\
	libj2_j2i_max_j2i_to_j2i.o\
	libj2_j2i_max_ji_to_j2i.o\
	libj2_j2i_max_j2i.o\
	libj2_j2i_max_ji.o\
	libj2_j2i_min_j2i_to_j2i.o\
	libj2_j2i_min_ji_to_j2i.o\
	libj2_j2i_min_j2i.o\
	libj2_j2i_min_ji.o\
	libj2_vmax_j2i.o\
	libj2_max_j2i.o\
	libj2_vmin_j2i.o\
	libj2_min_j2i.o\
	libj2_max_j2i_to_j2i.o\
	libj2_min_j2i_to_j2i.o\
	libj2_vmin_j2i_to_j2i.o\
	libj2_vmin_j2i_return.o\
	libj2_min_j2i_return.o\
	libj2_vmax_j2i_to_j2i.o\
	libj2_vmax_j2i_return.o\
	libj2_max_j2i_return.o\
	libj2_minus_j2i_to_j2i.o\
	libj2_minus_j2i.o\
	libj2_minus_j2i_to_j2u.o\
	libj2_minus_j2u_to_j2i.o\
	libj2_abs_j2i_to_j2i.o\
	libj2_abs_j2i.o\
	libj2_abs_j2i_to_j2u.o\
	libj2_minus_abs_j2i_to_j2i.o\
	libj2_minus_abs_j2i.o\
	libj2_j2i_xor_sign_to_j2i.o\
	libj2_j2i_xor_sign_to_j2u.o\
	libj2_j2i_xor_sign.o\
	libj2_j2i_cmp_j2u.o\
	libj2_j2u_cmp_j2i.o\
	libj2_ji_cmp_j2u.o\
	libj2_ju_cmp_j2i.o\
	libj2_j2i_cmp_ju.o\
	libj2_j2u_cmp_ji.o\
	libj2_j2i_lsh.o\
	libj2_j2i_lsh_to_j2i.o\
	libj2_ji_lsh_to_j2i.o\
	libj2_j2i_lsh_overflow.o\
	libj2_j2i_lsh_to_j2i_overflow.o\
	libj2_ji_lsh_to_j2i_overflow.o\
	libj2_j2i_rsh_to_j2i.o\
	libj2_j2i_rsh.o\
	libj2_ji_rsh_to_j2i.o\
	libj2_j2i_rsh_to_j2i_underflow.o\
	libj2_j2i_rsh_underflow.o\
	libj2_ji_rsh_to_j2i_underflow.o\
	libj2_j2i_lsh_overflow_p.o\
	libj2_ji_lsh_overflow_p.o\
	libj2_j2i_rsh_underflow_p.o\
	libj2_ji_rsh_underflow_p.o\
	libj2_j2i_add_j2i.o\
	libj2_j2i_add_j2i_overflow.o\
	libj2_j2i_add_j2i_overflow_p.o\
	libj2_j2i_add_j2i_to_j2i.o\
	libj2_j2i_add_j2i_to_j2i_overflow.o\
	libj2_j2i_add_ji.o\
	libj2_j2i_add_ji_overflow.o\
	libj2_j2i_add_ji_overflow_p.o\
	libj2_j2i_add_ji_to_j2i.o\
	libj2_j2i_add_ji_to_j2i_overflow.o\
	libj2_ji_add_j2i_overflow_p.o\
	libj2_ji_add_j2i_to_j2i.o\
	libj2_ji_add_j2i_to_j2i_overflow.o\
	libj2_ji_add_ji_to_j2i.o\
	libj2_j2i_rsub_j2i.o\
	libj2_j2i_rsub_j2i_overflow.o\
	libj2_j2i_rsub_j2i_overflow_p.o\
	libj2_j2i_rsub_ji.o\
	libj2_j2i_rsub_ji_overflow.o\
	libj2_j2i_rsub_ji_overflow_p.o\
	libj2_j2i_sub_j2i.o\
	libj2_j2i_sub_j2i_overflow.o\
	libj2_j2i_sub_j2i_overflow_p.o\
	libj2_j2i_sub_j2i_to_j2i.o\
	libj2_j2i_sub_j2i_to_j2i_overflow.o\
	libj2_j2i_sub_ji.o\
	libj2_j2i_sub_ji_overflow.o\
	libj2_j2i_sub_ji_overflow_p.o\
	libj2_j2i_sub_ji_to_j2i.o\
	libj2_j2i_sub_ji_to_j2i_overflow.o\
	libj2_ji_sub_j2i_overflow_p.o\
	libj2_ji_sub_j2i_to_j2i.o\
	libj2_ji_sub_j2i_to_j2i_overflow.o\
	libj2_ji_sub_ji_to_j2i.o\
	libj2_j2i_mul_j2i.o\
	libj2_j2i_mul_j2i_overflow.o\
	libj2_j2i_mul_j2i_overflow_p.o\
	libj2_j2i_mul_j2i_overflow_p_quick.o\
	libj2_j2i_mul_j2i_to_j2i.o\
	libj2_j2i_mul_j2i_to_j2i_overflow.o\
	libj2_j2i_mul_j2i_to_j2i_overflow_p.o\
	libj2_j2i_mul_ji.o\
	libj2_j2i_mul_ji_overflow.o\
	libj2_j2i_mul_ji_overflow_p.o\
	libj2_j2i_mul_ji_overflow_p_quick.o\
	libj2_j2i_mul_ji_to_j2i.o\
	libj2_j2i_mul_ji_to_j2i_overflow.o\
	libj2_j2i_mul_ji_to_j2i_overflow_p.o\
	libj2_ji_mul_j2i_overflow_p.o\
	libj2_ji_mul_j2i_overflow_p_quick.o\
	libj2_ji_mul_j2i_to_j2i.o\
	libj2_ji_mul_j2i_to_j2i_overflow.o\
	libj2_ji_mul_j2i_to_j2i_overflow_p.o\
	libj2_ji_mul_ji_to_j2i.o\
	libj2_j2i_div_j2i.o\
	libj2_j2i_div_j2i_return.o\
	libj2_j2i_div_j2i_to_j2i.o\
	libj2_j2i_div_j2i_to_j2i_underflow.o\
	libj2_j2i_div_j2i_underflow.o\
	libj2_j2i_div_ji.o\
	libj2_j2i_div_ji_return.o\
	libj2_j2i_div_ji_to_j2i.o\
	libj2_j2i_div_ji_to_j2i_underflow.o\
	libj2_j2i_div_ji_underflow.o\
	libj2_j2i_divmod_j2i.o\
	libj2_j2i_divmod_j2i_to_j2i.o\
	libj2_j2i_divmod_j2i_to_j2i_j2i.o\
	libj2_j2i_divmod_ji.o\
	libj2_j2i_divmod_ji_to_j2i.o\
	libj2_j2i_divmod_ji_to_j2i_j2i.o\
	libj2_j2i_mod_j2i.o\
	libj2_j2i_mod_j2i_to_j2i.o\
	libj2_j2i_mod_ji.o\
	libj2_j2i_mod_ji_to_j2i.o\
	libj2_j2i_rdiv_j2i.o\
	libj2_j2i_rdiv_j2i_underflow.o\
	libj2_j2i_rdivmod_j2i.o\
	libj2_j2i_rdivmod_j2i_to_j2i.o\
	libj2_j2i_rmod_j2i.o

SUBHDR =\
	libj2/constants.h\
	libj2/signum.h\
	libj2/constructors.h\
	libj2/unsigned-comparsion.h\
	libj2/signed-comparsion.h\
	libj2/mixed-comparsion.h\
	libj2/bitwise-logic.h\
	libj2/sign-shifting.h\
	libj2/bit-shifting.h\
	libj2/bit-scanning.h\
	libj2/addition.h\
	libj2/subtraction.h\
	libj2/multiplication.h\
	libj2/division.h\
	libj2/saturated-math.h\
	libj2/strings.h

HDR =\
	$(SUBHDR)\
	libj2.h\
	common.h

LOBJ = $(OBJ:.o=.lo)
TOBJ = $(OBJ:.o=.to)
TEST = $(OBJ:.o=.t)

MAN0 = libj2.h.0
MAN7 = libj2.7
MAN3 =\
	LIBJ2_JU_BIT.3\
	LIBJ2_J2U_BIT.3\
	LIBJ2_J2I_BIT.3\
	LIBJ2_J2I_VBIT.3\
	struct_libj2_j2u.3\
	libj2_j2u.3\
	struct_libj2_j2i.3\
	libj2_j2i.3\
	enum_libj2_overflow.3\
	libj2_overflow.3\
	LIBJ2_NO_OVERFLOW.3\
	LIBJ2_OVERFLOW.3\
	LIBJ2_OVERFLOW_UNKNOWN.3\
	LIBJ2_POSITIVE_OVERFLOW_UNKNOWN.3\
	LIBJ2_POSITIVE_OVERFLOW.3\
	LIBJ2_NEGATIVE_OVERFLOW_UNKNOWN.3\
	LIBJ2_NEGATIVE_OVERFLOW.3


all: libj2.a libj2.$(LIBEXT) $(TEST)
$(OBJ): $(HDR)
$(LOBJ): $(HDR)
$(TOBJ): $(HDR)
$(TEST): libj2.a

.c.o:
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

.c.to:
	$(CC) -c -o $@ $< -DTEST $(CFLAGS) $(CPPFLAGS)

.to.t:
	$(CC) -o $@ $< libj2.a $(LDFLAGS)

.c.t:
	$(CC) -o $@ $< libj2.a -DTEST $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

.c.lo:
	$(CC) -fPIC -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

libj2.a: $(OBJ)
	@rm -f -- $@
	$(AR) rc $@ $(OBJ)
	$(AR) ts $@ > /dev/null

libj2.$(LIBEXT): $(LOBJ)
	$(CC) $(LIBFLAGS) -o $@ $(LOBJ) $(LDFLAGS)

check: $(TEST)
	@set -e;\
	for t in $(TEST); do\
		printf '%s ' $(CHECK_PREFIX) "./$$t"; printf '\n';\
		$(CHECK_PREFIX) ./"$$t";\
	done

makefile-check:
	grep '\.o\\\{0,1\}$$' < Makefile |\
		sed 's/^'"$$(printf '\t')"'//' |\
		sed 's/\.o\\\{0,1\}$$/\.c/' |\
		sort |\
		diff -u <(printf '%s\n' *.c | sort) -

install: libj2.a libj2.$(LIBEXT)
	mkdir -p -- "$(DESTDIR)$(PREFIX)/lib"
	mkdir -p -- "$(DESTDIR)$(PREFIX)/include/libj2"
	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man0"
	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man3"
	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man7"
	cp -- libj2.a "$(DESTDIR)$(PREFIX)/lib/"
	cp -- libj2.$(LIBEXT) "$(DESTDIR)$(PREFIX)/lib/libj2.$(LIBMINOREXT)"
	$(FIX_INSTALL_NAME) "$(DESTDIR)$(PREFIX)/lib/libj2.$(LIBMINOREXT)"
	ln -sf -- libj2.$(LIBMINOREXT) "$(DESTDIR)$(PREFIX)/lib/libj2.$(LIBMAJOREXT)"
	ln -sf -- libj2.$(LIBMAJOREXT) "$(DESTDIR)$(PREFIX)/lib/libj2.$(LIBEXT)"
	cp -- libj2.h "$(DESTDIR)$(PREFIX)/include/"
	cp -- $(SUBHDR) "$(DESTDIR)$(PREFIX)/include/libj2/"
	cp -P -- $(MAN0) "$(DESTDIR)$(MANPREFIX)/man0/"
	cp -P -- $(MAN3) "$(DESTDIR)$(MANPREFIX)/man3/"
	cp -P -- $(MAN7) "$(DESTDIR)$(MANPREFIX)/man7/"

uninstall:
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libj2.a"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libj2.$(LIBMAJOREXT)"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libj2.$(LIBMINOREXT)"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libj2.$(LIBEXT)"
	-rm -f -- "$(DESTDIR)$(PREFIX)/include/libj2.h"
	-cd -- "$(DESTDIR)$(PREFIX)/include/" && rm -f -- $(SUBHDR)
	-rmdir -- "$(DESTDIR)$(PREFIX)/include/libj2"
	-cd -- "$(DESTDIR)$(MANPREFIX)/man0/" && rm -f -- $(MAN0)
	-cd -- "$(DESTDIR)$(MANPREFIX)/man3/" && rm -f -- $(MAN3)
	-cd -- "$(DESTDIR)$(MANPREFIX)/man7/" && rm -f -- $(MAN7)

clean:
	-rm -f -- *.o *.a *.lo *.su *.so *.so.* *.dll *.dylib
	-rm -f -- *.gch *.gcov *.gcno *.gcda *.$(LIBEXT)
	-rm -f -- *.to *.t

.SUFFIXES:
.SUFFIXES: .lo .o .c .to .t

.PHONY: all check release-check install uninstall clean
