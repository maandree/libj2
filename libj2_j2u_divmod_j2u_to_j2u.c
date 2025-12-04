/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_divmod_j2u_to_j2u(struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res_q);
/* TODO Add man page */


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
validate_result(const struct libj2_j2u *a, const struct libj2_j2u *b,
                const struct libj2_j2u *q, const struct libj2_j2u *r)
{
	struct libj2_j2u v;
	libj2_j2u_mul_j2u_to_j2u(q, b, &v);
	libj2_j2u_add_j2u(&v, r);
	EXPECT(libj2_j2u_eq_j2u(&v, a));

	if (!a->high && !b->high) {
		EXPECT(!q->high);
		EXPECT(!r->high);
		EXPECT(q->low == a->low / b->low);
		EXPECT(r->low == a->low % b->low);
	}
}


static void
check_manual(const struct libj2_j2u *a, const struct libj2_j2u *b,
             const struct libj2_j2u *expected_q, const struct libj2_j2u *expected_r)
{
	struct libj2_j2u a_saved = *a, b_saved = *b, q, r, eq, er;

	EXPECT(!libj2_j2u_is_zero(b));

	r = (struct libj2_j2u){111, 222};
	q = (struct libj2_j2u){333, 444};
	libj2_j2u_divmod_j2u_to_j2u_j2u(a, b, &q, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	if (expected_q) {
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
	} else {
		eq = q;
		expected_q = &eq;
	}
	if (expected_r) {
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));
	} else {
		er = r;
		expected_r = &er;
	}

	validate_result(a, b, expected_q, expected_r);

	r = (struct libj2_j2u){111, 222};
	q = *a;
	libj2_j2u_divmod_j2u_to_j2u_j2u(&q, b, &q, &r);
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	r = *a;
	q = (struct libj2_j2u){333, 444};
	libj2_j2u_divmod_j2u_to_j2u_j2u(&r, b, &q, &r);
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	r = (struct libj2_j2u){111, 222};
	q = *b;
	libj2_j2u_divmod_j2u_to_j2u_j2u(a, &q, &q, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	r = *b;
	q = (struct libj2_j2u){333, 444};
	libj2_j2u_divmod_j2u_to_j2u_j2u(a, &r, &q, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	r = *b;
	q = *a;
	libj2_j2u_divmod_j2u_to_j2u_j2u(&q, &r, &q, &r);
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	r = *a;
	q = *b;
	libj2_j2u_divmod_j2u_to_j2u_j2u(&r, &q, &q, &r);
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	q = (struct libj2_j2u){333, 444};
	libj2_j2u_div_j2u_to_j2u(a, b, &q);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));

	q = *a;
	libj2_j2u_div_j2u_to_j2u(&q, b, &q);
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));

	q = *b;
	libj2_j2u_div_j2u_to_j2u(a, &q, &q);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));

	r = (struct libj2_j2u){111, 222};
	libj2_j2u_mod_j2u_to_j2u(a, b, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	r = *a;
	libj2_j2u_mod_j2u_to_j2u(&r, b, &r);
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	r = *b;
	libj2_j2u_mod_j2u_to_j2u(a, &r, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	r = *a;
	q = (struct libj2_j2u){333, 444};
	libj2_j2u_divmod_j2u_to_j2u(&r, b, &q);
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	r = *a;
	q = *b;
	libj2_j2u_divmod_j2u_to_j2u(&r, &q, &q);
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	q = *a;
	libj2_j2u_div_j2u(&q, b);
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));

	r = *a;
	libj2_j2u_mod_j2u(&r, b);
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	r = *b;
	q = (struct libj2_j2u){333, 444};
	libj2_j2u_rdivmod_j2u_to_j2u(&r, a, &q);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	r = *b;
	q = *a;
	libj2_j2u_rdivmod_j2u_to_j2u(&r, &q, &q);
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	q = *b;
	libj2_j2u_rdiv_j2u(&q, a);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&q, expected_q));

	r = *b;
	libj2_j2u_rmod_j2u(&r, a);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	r = *a;
	EXPECT(libj2_j2u_divmod_j2u(&r, b) == expected_q->low);
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

	EXPECT(libj2_j2u_div_j2u_return(a, b) == expected_q->low);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));

	if (!b->high) {
		r = (struct libj2_j2u){111, 222};
		q = (struct libj2_j2u){333, 444};
		libj2_j2u_divmod_ju_to_j2u_j2u(a, b->low, &q, &r);
		EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		r = (struct libj2_j2u){111, 222};
		q = *a;
		libj2_j2u_divmod_ju_to_j2u_j2u(&q, b->low, &q, &r);
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		r = *a;
		q = (struct libj2_j2u){333, 444};
		libj2_j2u_divmod_ju_to_j2u_j2u(&r, b->low, &q, &r);
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		q = (struct libj2_j2u){333, 444};
		libj2_j2u_div_ju_to_j2u(a, b->low, &q);
		EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));

		q = *a;
		libj2_j2u_div_ju_to_j2u(&q, b->low, &q);
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));

		r = (struct libj2_j2u){111, 222};
		libj2_j2u_mod_ju_to_j2u(a, b->low, &r);
		EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		r = *a;
		libj2_j2u_mod_ju_to_j2u(&r, b->low, &r);
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		r = *a;
		q = (struct libj2_j2u){333, 444};
		libj2_j2u_divmod_ju_to_j2u(&r, b->low, &q);
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		q = *a;
		libj2_j2u_div_ju(&q, b->low);
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));

		r = *a;
		libj2_j2u_mod_ju(&r, b->low);
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		r = *b;
		EXPECT(libj2_j2u_rdivmod_j2u(&r, a) == expected_q->low);
		EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		r = *a;
		EXPECT(libj2_j2u_divmod_ju(&r, b->low) == expected_q->low);
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		EXPECT(libj2_j2u_div_ju_return(a, b->low) == expected_q->low);
		EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	}

	if (a == b) {
		r = (struct libj2_j2u){111, 222};
		q = *a;
		libj2_j2u_divmod_j2u_to_j2u_j2u(&q, &q, &q, &r);
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		r = *a;
		q = (struct libj2_j2u){333, 444};
		libj2_j2u_divmod_j2u_to_j2u_j2u(&r, &r, &q, &r);
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		q = *a;
		libj2_j2u_div_j2u_to_j2u(&q, &q, &q);
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));

		r = *a;
		libj2_j2u_mod_j2u_to_j2u(&r, &r, &r);
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		r = *a;
		q = (struct libj2_j2u){333, 444};
		libj2_j2u_divmod_j2u_to_j2u(&r, &r, &q);
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		q = *a;
		libj2_j2u_div_j2u(&q, &q);
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));

		r = *a;
		libj2_j2u_mod_j2u(&r, &r);
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		r = *a;
		q = (struct libj2_j2u){333, 444};
		libj2_j2u_rdivmod_j2u_to_j2u(&r, &r, &q);
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		q = *a;
		libj2_j2u_rdiv_j2u(&q, &q);
		EXPECT(libj2_j2u_eq_j2u(&q, expected_q));

		r = *a;
		libj2_j2u_rmod_j2u(&r, &r);
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));

		r = *a;
		EXPECT(libj2_j2u_divmod_j2u(&r, &r) == expected_q->low);
		EXPECT(libj2_j2u_eq_j2u(&r, expected_r));
	}
}


static void
check(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u u, v;
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
		b = &u;
	}
	check_manual(a, b, NULL, NULL);
}


int
main(void)
{
	struct libj2_j2u a = {0, 0}, b = {0, 0}, q = {0, 0}, r = {0, 0};
	struct libj2_j2u zero = {0, 0}, one = {0, 0}, two = {0, 0};
	unsigned i;

	srand((unsigned)time(NULL));

	one.low = 1;
	two.low = 2;

	check_manual(&one, &one, &one, &zero);
	check_manual(&two, &one, &two, &zero);
	check_manual(&one, &two, &zero, &one);
	check_manual(&zero, &one, &zero, &zero);

	a.low = 35;
	b.low = 4;
	q.low = 8;
	r.low = 3;
	check_manual(&a, &b, &q, &r);

	a.low = UINTMAX_C(0x94385c048097d350);
	b.low = UINTMAX_C(0x9212734e33d9df1e);
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
		if (!libj2_j2u_is_zero(&a))
			check_manual(&zero, &a, &zero, &zero);
		check_manual(&a, &one, &a, &zero);
		b.high = a.high >> 1;
		b.low = a.low >> 1;
		b.low |= (a.high & 1U) << (LIBJ2_JU_BIT - 1U);
		check_manual(&a, &two, &b, (a.low & 1U) ? &one : &zero);
	}

	return 0;
}


#endif
