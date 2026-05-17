/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_divmod_j2i_to_j2i(struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res_q);


#else

static uintmax_t
random_ju(void)
{
	size_t n = LIBJ2_JU_BIT;
	uintmax_t r = 0;
	while (n--)
		if (rand() < rand())
			r |= (uintmax_t)1 << n;
	return r;
}


static void
validate_result(const struct libj2_j2i *a, const struct libj2_j2i *b,
                const struct libj2_j2i *q, const struct libj2_j2i *r)
{
	struct libj2_j2i v;
	libj2_j2i_mul_j2i_to_j2i(q, b, &v);
	libj2_j2i_add_j2i(&v, r);
	EXPECT(libj2_j2i_eq_j2i(&v, a));

	if (!a->high && !b->high) {
		EXPECT(!q->high);
		EXPECT(!r->high);
		EXPECT(q->low == a->low / b->low);
		EXPECT(r->low == a->low % b->low);
	}
}


static void
check_manual(const struct libj2_j2i *a, const struct libj2_j2i *b,
             const struct libj2_j2i *expected_q, const struct libj2_j2i *expected_r)
{
	struct libj2_j2i a_saved = *a, b_saved = *b, q, r, eq, er;
	intmax_t b_low_ji;
	int underflow;

	EXPECT(!libj2_j2i_is_zero(b));

	r = (struct libj2_j2i){111, 222};
	q = (struct libj2_j2i){333, 444};
	libj2_j2i_divmod_j2i_to_j2i_j2i(a, b, &q, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	if (expected_q) {
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
	} else {
		eq = q;
		expected_q = &eq;
	}
	if (expected_r) {
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));
	} else {
		er = r;
		expected_r = &er;
	}
	underflow = !libj2_j2i_is_zero(expected_r);

	validate_result(a, b, expected_q, expected_r);

	r = (struct libj2_j2i){111, 222};
	q = *a;
	libj2_j2i_divmod_j2i_to_j2i_j2i(&q, b, &q, &r);
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	r = *a;
	q = (struct libj2_j2i){333, 444};
	libj2_j2i_divmod_j2i_to_j2i_j2i(&r, b, &q, &r);
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	r = (struct libj2_j2i){111, 222};
	q = *b;
	libj2_j2i_divmod_j2i_to_j2i_j2i(a, &q, &q, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	r = *b;
	q = (struct libj2_j2i){333, 444};
	libj2_j2i_divmod_j2i_to_j2i_j2i(a, &r, &q, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	r = *b;
	q = *a;
	libj2_j2i_divmod_j2i_to_j2i_j2i(&q, &r, &q, &r);
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	r = *a;
	q = *b;
	libj2_j2i_divmod_j2i_to_j2i_j2i(&r, &q, &q, &r);
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	q = (struct libj2_j2i){333, 444};
	libj2_j2i_div_j2i_to_j2i(a, b, &q);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

	q = *a;
	libj2_j2i_div_j2i_to_j2i(&q, b, &q);
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

	q = *b;
	libj2_j2i_div_j2i_to_j2i(a, &q, &q);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

	q = (struct libj2_j2i){333, 444};
	EXPECT(libj2_j2i_div_j2i_to_j2i_underflow(a, b, &q) == underflow);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

	q = *a;
	EXPECT(libj2_j2i_div_j2i_to_j2i_underflow(&q, b, &q) == underflow);
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

	q = *b;
	EXPECT(libj2_j2i_div_j2i_to_j2i_underflow(a, &q, &q) == underflow);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

	r = (struct libj2_j2i){111, 222};
	libj2_j2i_mod_j2i_to_j2i(a, b, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	r = *a;
	libj2_j2i_mod_j2i_to_j2i(&r, b, &r);
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	r = *b;
	libj2_j2i_mod_j2i_to_j2i(a, &r, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	r = *a;
	q = (struct libj2_j2i){333, 444};
	libj2_j2i_divmod_j2i_to_j2i(&r, b, &q);
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	r = *a;
	q = *b;
	libj2_j2i_divmod_j2i_to_j2i(&r, &q, &q);
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	q = *a;
	libj2_j2i_div_j2i(&q, b);
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

	q = *a;
	EXPECT(libj2_j2i_div_j2i_underflow(&q, b) == underflow);
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

	r = *a;
	libj2_j2i_mod_j2i(&r, b);
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	r = *b;
	q = (struct libj2_j2i){333, 444};
	libj2_j2i_rdivmod_j2i_to_j2i(&r, a, &q);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	r = *b;
	q = *a;
	libj2_j2i_rdivmod_j2i_to_j2i(&r, &q, &q);
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	q = *b;
	libj2_j2i_rdiv_j2i(&q, a);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

	q = *b;
	EXPECT(libj2_j2i_rdiv_j2i_underflow(&q, a) == underflow);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

	r = *b;
	libj2_j2i_rmod_j2i(&r, a);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	r = *a;
	EXPECT(libj2_j2i_divmod_j2i(&r, b) == (intmax_t)expected_q->low);
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

	EXPECT(libj2_j2i_div_j2i_return(a, b) == (intmax_t)expected_q->low);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));

	if (!b->high && b->low <= (intmax_t)INTMAX_MAX) {
		b_low_ji = (intmax_t)b->low;

		r = (struct libj2_j2i){111, 222};
		q = (struct libj2_j2i){333, 444};
		libj2_j2i_divmod_ji_to_j2i_j2i(a, b_low_ji, &q, &r);
		EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		r = (struct libj2_j2i){111, 222};
		q = *a;
		libj2_j2i_divmod_ji_to_j2i_j2i(&q, b_low_ji, &q, &r);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		r = *a;
		q = (struct libj2_j2i){333, 444};
		libj2_j2i_divmod_ji_to_j2i_j2i(&r, b_low_ji, &q, &r);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		q = (struct libj2_j2i){333, 444};
		libj2_j2i_div_ji_to_j2i(a, b_low_ji, &q);
		EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

		q = *a;
		libj2_j2i_div_ji_to_j2i(&q, b_low_ji, &q);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

		q = (struct libj2_j2i){333, 444};
		EXPECT(libj2_j2i_div_ji_to_j2i_underflow(a, b_low_ji, &q) == underflow);
		EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

		q = *a;
		EXPECT(libj2_j2i_div_ji_to_j2i_underflow(&q, b_low_ji, &q) == underflow);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

		r = (struct libj2_j2i){111, 222};
		libj2_j2i_mod_ji_to_j2i(a, b_low_ji, &r);
		EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		r = *a;
		libj2_j2i_mod_ji_to_j2i(&r, b_low_ji, &r);
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		r = *a;
		q = (struct libj2_j2i){333, 444};
		libj2_j2i_divmod_ji_to_j2i(&r, b_low_ji, &q);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		q = *a;
		libj2_j2i_div_ji(&q, b_low_ji);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

		q = *a;
		EXPECT(libj2_j2i_div_ji_underflow(&q, b_low_ji) == underflow);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

		r = *a;
		libj2_j2i_mod_ji(&r, b_low_ji);
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		r = *b;
		EXPECT(libj2_j2i_rdivmod_j2i(&r, a) == (intmax_t)expected_q->low);
		EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		r = *a;
		EXPECT(libj2_j2i_divmod_ji(&r, b_low_ji) == (intmax_t)expected_q->low);
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		EXPECT(libj2_j2i_div_ji_return(a, b_low_ji) == (intmax_t)expected_q->low);
		EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	}

	if (a == b) {
		r = (struct libj2_j2i){111, 222};
		q = *a;
		libj2_j2i_divmod_j2i_to_j2i_j2i(&q, &q, &q, &r);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		r = *a;
		q = (struct libj2_j2i){333, 444};
		libj2_j2i_divmod_j2i_to_j2i_j2i(&r, &r, &q, &r);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		q = *a;
		libj2_j2i_div_j2i_to_j2i(&q, &q, &q);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

		q = *a;
		EXPECT(libj2_j2i_div_j2i_to_j2i_underflow(&q, &q, &q) == underflow);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

		r = *a;
		libj2_j2i_mod_j2i_to_j2i(&r, &r, &r);
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		r = *a;
		q = (struct libj2_j2i){333, 444};
		libj2_j2i_divmod_j2i_to_j2i(&r, &r, &q);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		q = *a;
		libj2_j2i_div_j2i(&q, &q);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

		q = *a;
		EXPECT(libj2_j2i_div_j2i_underflow(&q, &q) == underflow);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

		r = *a;
		libj2_j2i_mod_j2i(&r, &r);
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		r = *a;
		q = (struct libj2_j2i){333, 444};
		libj2_j2i_rdivmod_j2i_to_j2i(&r, &r, &q);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		q = *a;
		libj2_j2i_rdiv_j2i(&q, &q);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

		q = *a;
		EXPECT(libj2_j2i_rdiv_j2i_underflow(&q, &q) == underflow);
		EXPECT(libj2_j2i_eq_j2i(&q, expected_q));

		r = *a;
		libj2_j2i_rmod_j2i(&r, &r);
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));

		r = *a;
		EXPECT(libj2_j2i_divmod_j2i(&r, &r) == (intmax_t)expected_q->low);
		EXPECT(libj2_j2i_eq_j2i(&r, expected_r));
	}
}


static void
check(const struct libj2_j2i *a, const struct libj2_j2i *b)
{
	struct libj2_j2i u, v;
	if (!a) {
		u.high = random_ju();
		u.low = random_ju();
		a = &u;
	}
	if (!b) {
		do {
			v.high = random_ju();
			v.low = random_ju();
		} while (!v.high && !v.low);
		b = &v;
	}
	check_manual(a, b, NULL, NULL);
}


int
main(void)
{
	struct libj2_j2i a = {0, 0}, b = {0, 0}, q = {0, 0}, r = {0, 0};
	struct libj2_j2i zero = {0, 0}, one = {0, 0}, two = {0, 0}, minus_one;
	unsigned i;

	srand((unsigned)time(NULL));

	one.low = 1;
	two.low = 2;
	libj2_ji_to_j2i(-1, &minus_one);

	check_manual(&one, &one, &one, &zero);
	check_manual(&two, &one, &two, &zero);
	check_manual(&one, &two, &zero, &one);
	check_manual(&zero, &one, &zero, &zero);

	a.low = 35;
	b.low = 4;
	q.low = 8;
	r.low = 3;
	check_manual(&a, &b, &q, &r);

	a.low = UINTMAX_C(0x14385c048097d350);
	b.low = UINTMAX_C(0x1212734e33d9df1e);
	r.low = a.low % b.low;
	check(&a, &b);
	check_manual(&a, &b, &one, &r);

	for (i = 0; i < 2048; i++) {
		a.high = b.high = 0;
		a.low = random_ju();
		b.low = random_ju();
		check(NULL, NULL);
		check(NULL, &a);
		check(&a, NULL);
		check(&a, &b);
		a.high = b.low;
		check(&a, &a);
		if (!libj2_j2i_is_zero(&a))
			check_manual(&zero, &a, &zero, &zero);
		check_manual(&a, &one, &a, &zero);
		b.high = a.high >> 1;
		b.low = a.low >> 1;
		b.low |= (a.high & 1U) << (LIBJ2_JU_BIT - 1U);
		if (a.high & ((uintmax_t)INTMAX_MAX + 1U)) {
			b.high |= (uintmax_t)INTMAX_MAX + 1U;
			if (a.low & 1U) {
				b.low += 1U;
				if (b.low == 0U)
					b.high += 1U;
				check_manual(&a, &two, &b, &minus_one);
			} else {
				check_manual(&a, &two, &b, &zero);
			}
		} else {
			check_manual(&a, &two, &b, (a.low & 1U) ? &one : &zero);
		}
	}

	/* TODO test sign-issues in a better way, especially ji divisor */

	libj2_j2i_min(&a);
	libj2_j2i_min(&b);
	check_manual(&a, &minus_one, &b, &zero);

	return 0;
}

#endif
