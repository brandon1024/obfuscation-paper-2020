#include <stdio.h>
#include <gmp.h>

int main(int argc, char *argv[]) {
	mpz_t a, p, e, r;

	mpz_init_set_str(a, "96988", 10);
	mpz_init_set_str(p, "A72754B749C1", 13);
	mpz_init_set(e, p);
	mpz_sub_ui(e, e, 1);

	mpz_init(r);
	mpz_powm(r, a, e, p);
	mpz_mul_ui(r, r, 617);
	mpz_add_ui(r, r, 407);

	mpz_out_str(stdout, 10, r);

	mpz_clears(a, p, e, r, NULL);
	return 0;
}
