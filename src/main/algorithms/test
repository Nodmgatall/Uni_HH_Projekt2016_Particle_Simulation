
#include <vector>

typedef double data_type __attribute__ ((aligned (8)));
data_type      A_ij = 88 * 1;
data_type      B_ij = 28 * 1;
data_type      m_i  = 1;
data_type      m_j  = 1;

void step_2 (data_type& __restrict__ p_position_aix,
             data_type& __restrict__ p_position_aiy,
             data_type& __restrict__ p_position_aiz,
             data_type& __restrict__ p_position_bix,
             data_type& __restrict__ p_position_biy,
             data_type& __restrict__ p_position_biz,
             data_type* __restrict__ p_position_ajx,
             data_type* __restrict__ p_position_ajy,
             data_type* __restrict__ p_position_ajz,
             data_type* __restrict__ p_position_bjx,
             data_type* __restrict__ p_position_bjy,
             data_type* __restrict__ p_position_bjz,
             unsigned long p_index_j_begin,
             unsigned long p_index_j_end) {
    unsigned long count_of_dist_calculations = p_index_j_end - p_index_j_begin;

    data_type distances_x[count_of_dist_calculations] __attribute__ ((aligned (8)));
    data_type distances_y[count_of_dist_calculations] __attribute__ ((aligned (8)));
    data_type distances_z[count_of_dist_calculations] __attribute__ ((aligned (8)));
    data_type temp_x;
    data_type temp_y;
    data_type temp_z;

    for (unsigned long i = 0, other = p_index_j_begin + i; i < count_of_dist_calculations; i++, other++) {
        temp_x         = p_position_ajx[other] - p_position_aix;
        distances_x[i] = temp_x * temp_x;
        temp_y         = p_position_ajy[other] - p_position_aiy;
        distances_y[i] = temp_y * temp_y;
        temp_z         = p_position_ajz[other] - p_position_aiz;
        distances_z[i] = temp_z * temp_z;
    }
    data_type r_ij_2;
    data_type r_ij_8;
    data_type r_ij_6;
    data_type r_ij_18;
    data_type s_ij;
    data_type s_ij_x;
    data_type s_ij_y;
    data_type s_ij_z;
    for (unsigned long j = 0, k = j + p_index_j_begin; j < count_of_dist_calculations; j++, k++) {
        // Distance vector calculation
        // distance scalar squared cal
        r_ij_2  = distances_x[j] + distances_y[j] + distances_z[j];
        r_ij_8  = r_ij_2 * r_ij_2;
        r_ij_6  = r_ij_2 * r_ij_8;
        r_ij_18 = r_ij_6 * r_ij_6 * r_ij_2;
        s_ij    = (A_ij - B_ij * r_ij_6) / (r_ij_18);
        s_ij_x  = s_ij * distances_x[j];
        s_ij_y  = s_ij * distances_y[j];
        s_ij_z  = s_ij * distances_z[j];
    }
    for (unsigned long j = 0, k = j + p_index_j_begin; j < count_of_dist_calculations; j++, k++) {
        temp_x = p_position_bix - s_ij_x / m_i;
        temp_y = p_position_biy - s_ij_y / m_i;
        temp_z = p_position_biz - s_ij_z / m_i;
        p_position_bix = temp_x;
        p_position_biy = temp_y;
        p_position_biz = temp_x;
        p_position_bjx[k] += s_ij_x / m_j;
        p_position_bjy[k] += s_ij_y / m_j;
        p_position_bjz[k] += s_ij_z / m_j;
    }
}
/*
int main () {
    data_type x[10000] __attribute__ ((aligned (8)));
    data_type y[10000] __attribute__ ((aligned (8)));
    data_type z[10000] __attribute__ ((aligned (8)));

    data_type x_old[10000] __attribute__ ((aligned (8)));
    data_type y_old[10000] __attribute__ ((aligned (8)));
    data_type z_old[10000] __attribute__ ((aligned (8)));

    step_2 (x[0], y[0], z[0], x_old[0], y_old[0], z_old[0], &x[0], &y[0], &z[0], &x_old[0], &y_old[0], &z_old[0], 0, 10000);
    return 0;
}
*/
