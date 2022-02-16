#include "FilterTransfer.h"

TF2d bilinearTransform2(const TF2d &atf, double sampleRate, double warpFactor)
{
    const double *B = atf.b();
    const double *A = atf.a();

    double B0 = B[0], B1 = B[1], B2 = B[2];
    double A0 = A[0], A1 = A[1], A2 = A[2];

    TF2d dtf;
    double *b = dtf.b();
    double *a = dtf.a();
    double k = 2.0*sampleRate*warpFactor;
    b[0] = k*k*B2 + k*B1 + B0;
    b[1] = k*k*-2.0*B2 + 2.0*B0;
    b[2] = k*k*B2 - k*B1 + B0;
    a[0] = k*k*A2 + k*A1 + A0;
    a[1] = k*k*-2.0*A2 + 2.0*A0;
    a[2] = k*k*A2 - k*A1 + A0;

    return dtf.normalized();
}

TF3d bilinearTransform3(const TF3d &atf, double sampleRate, double warpFactor)
{
    const double *B = atf.b();
    const double *A = atf.a();

    double B0 = B[0], B1 = B[1], B2 = B[2], B3 = B[3];
    double A0 = A[0], A1 = A[1], A2 = A[2], A3 = A[3];

    TF3d dtf;
    double *b = dtf.b();
    double *a = dtf.a();
    double k = 2.0*sampleRate*warpFactor;
    b[0] = k*k*k*B3 + k*k*B2 + B1*k + B0;
    b[1] = k*k*k*-3.0*B3 - k*k*B2 + B1*k + 3.0*B0;
    b[2] = k*k*k*3.0*B3 - k*k*B2 - B1*k + 3.0*B0;
    b[3] = k*k*k*-1.0*B3 + k*k*B2 - B1*k + B0;
    a[0] = k*k*k*A3 + k*k*A2 + A1*k + A0;
    a[1] = k*k*k*-3.0*A3 - k*k*A2 + A1*k + 3.0*A0;
    a[2] = k*k*k*3.0*A3 - k*k*A2 - A1*k + 3.0*A0;
    a[3] = k*k*k*-1.0*A3 + k*k*A2 - A1*k + A0;

    return dtf.normalized();
}

TF6d bilinearTransform6(const TF6d &atf, double sampleRate, double warpFactor)
{
    const double *B = atf.b();
    const double *A = atf.a();

    double B0 = B[0], B1 = B[1], B2 = B[2], B3 = B[3],
           B4 = B[4], B5 = B[5], B6 = B[6];
    double A0 = A[0], A1 = A[1], A2 = A[2], A3 = A[3],
           A4 = A[4], A5 = A[5], A6 = A[6];

    TF6d dtf;
    double *b = dtf.b();
    double *a = dtf.a();
    double k = 2.0*sampleRate*warpFactor;
    b[0] = B6*(k*k*k*k*k*k) + B5*(k*k*k*k*k) + B4*(k*k*k*k) + B3*(k*k*k) + B2*(k*k) + B1*k + B0;
    b[1] = -6.0*B6*(k*k*k*k*k*k) - 4.0*B5*(k*k*k*k*k) - 2.0*B4*(k*k*k*k) + 2.0*B2*(k*k) + 4.0*B1*k + 6.0*B0;
    b[2] = 15.0*B6*(k*k*k*k*k*k) + 5.0*B5*(k*k*k*k*k) - B4*(k*k*k*k) - 3.0*B3*(k*k*k) - B2*(k*k) + 5.0*B1*k + 15.0*B0;
    b[3] = -20.0*B6*(k*k*k*k*k*k) + 4.0*B4*(k*k*k*k) - 4.0*B2*(k*k) + 20.0*B0;
    b[4] = 15.0*B6*(k*k*k*k*k*k) - 5.0*B5*(k*k*k*k*k) - B4*(k*k*k*k) + 3.0*B3*(k*k*k) - B2*(k*k) - 5.0*B1*k + 15.0*B0;
    b[5] = -6.0*B6*(k*k*k*k*k*k) + 4.0*B5*(k*k*k*k*k) - 2.0*B4*(k*k*k*k) + 2.0*B2*(k*k) - 4.0*B1*k + 6.0*B0;
    b[6] = B6*(k*k*k*k*k*k) - B5*(k*k*k*k*k) + B4*(k*k*k*k) - B3*(k*k*k) + B2*(k*k) - B1*k + B0;
    a[0] = A6*(k*k*k*k*k*k) + A5*(k*k*k*k*k) + A4*(k*k*k*k) + A3*(k*k*k) + A2*(k*k) + A1*k + A0;
    a[1] = -6.0*A6*(k*k*k*k*k*k) - 4.0*A5*(k*k*k*k*k) - 2.0*A4*(k*k*k*k) + 2.0*A2*(k*k) + 4.0*A1*k + 6.0*A0;
    a[2] = 15.0*A6*(k*k*k*k*k*k) + 5.0*A5*(k*k*k*k*k) - A4*(k*k*k*k) - 3.0*A3*(k*k*k) - A2*(k*k) + 5.0*A1*k + 15.0*A0;
    a[3] = -20.0*A6*(k*k*k*k*k*k) + 4.0*A4*(k*k*k*k) - 4.0*A2*(k*k) + 20.0*A0;
    a[4] = 15.0*A6*(k*k*k*k*k*k) - 5.0*A5*(k*k*k*k*k) - A4*(k*k*k*k) + 3.0*A3*(k*k*k) - A2*(k*k) - 5.0*A1*k + 15.0*A0;
    a[5] = -6.0*A6*(k*k*k*k*k*k) + 4.0*A5*(k*k*k*k*k) - 2.0*A4*(k*k*k*k) + 2.0*A2*(k*k) - 4.0*A1*k + 6.0*A0;
    a[6] = A6*(k*k*k*k*k*k) - A5*(k*k*k*k*k) + A4*(k*k*k*k) - A3*(k*k*k) + A2*(k*k) - A1*k + A0;

    return dtf.normalized();
}
