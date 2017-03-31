/*
 * Description: 
 *     History: yang@haipo.me, 2017/03/17, create
 */

# include "ut_decimal.h"

mpd_context_t mpd_ctx;

mpd_t *mpd_one;
mpd_t *mpd_ten;
mpd_t *mpd_zero;

int init_mpd(void)
{
    mpd_ieee_context(&mpd_ctx, MPD_DECIMAL128);

    mpd_one = mpd_new(&mpd_ctx);
    mpd_set_string(mpd_one, "1", &mpd_ctx);
    mpd_ten = mpd_new(&mpd_ctx);
    mpd_set_string(mpd_ten, "10", &mpd_ctx);
    mpd_zero = mpd_new(&mpd_ctx);
    mpd_set_string(mpd_zero, "0", &mpd_ctx);

    return 0;
}

mpd_t *decimal(const char *str, int prec)
{
    mpd_t *result = mpd_new(&mpd_ctx);
    mpd_ctx.status = 0;
    mpd_set_string(result, str, &mpd_ctx);
    if (mpd_ctx.status == MPD_Conversion_syntax) {
        mpd_del(result);
        return NULL;
    }

    mpd_rescale(result, result, -prec, &mpd_ctx);
    return result;
}

