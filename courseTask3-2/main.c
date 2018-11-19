#include<stdio.h>
#include<stdlib.h>
int main(void) {
    
    /**
     * �����������, ��� ������������ ��� b = 5.
     * ��� �������, ����� ��� ����������, � ���������� c, b, y, n ��������� ������:
     * c = 0x0028FEDB, b = 0x0028FED0, y = 0x0028FEC8, n = 0x0028FEB8
     */
    char *p, c;
    int *a, b;
    float *x, y = 3.5;
    double *m, n;

    /**
     * ����� �������.
     */
    printf("Variable pointers: c=%p, b=%p, y=%p, n=%p, p=%p, a=%p, x=%p, m=%p\n", &c, &b, &y, &n, &p, &a, &x, &m);

    /**
     * �������� ��������� a ������ ����� 0x0028FED0, ��� ��������� �� ���������� ���������� b.
     */
    a = &b;

    printf("  Enter b = ");
    
    /* ������: scan("%d", a); */
    /**
     * �� ������ 0x0028FED0 (��������� a) ������������ ��������, ��������� �� ������ �����.
     * �����������, ��� ������������ ��� 5.
     * ��������� ��������� a ��������� �� ���������� ���������� b, �������� b ������ ����� 5.
     */
    scanf("%d", a);
    
    /**
     * ����� ��������:
     * a=0028FED0      *a=5    b=5
     * a=0028FED0, ������ ��� ��������� �� ��������� � ��������� �� b, � ����� b = 0x0028FED0.
     * *a=5, ������ ��� a ��������� �� ���������� b, � ������� �������� �������� 5.
     * b=5, ������ ��� ���������� ���������� b ����� 5
     */
    printf("a=%p\t*a=%d\tb=%d\n", a, *a, b);
    
    /* ������: p = a; */
    /**
     * �������������� ���������:
     * ������ p ��������� ���� ��, ���� � ��������� a (a ��������� �� ���������� ���������� b).
     * ��������� ��������� ������ �����, ��� ��������������� p ��������� ������ ���� ���������� b.
     * p ������ ����� 0x0028FED0
     */
    p = (char*)a;
    
    /**
     * ���������� �� ��������� p � �������� �� ���� ��������.
     * ��� �������� = ������ ���� ���������� b, �������� ������� ����� 5.
     * ��� ��� 5 �� ������� �� ������� ������ �����, � c ����� �������� 5.
     */
    c=*p; /* � c ���������� �������� �� ������ p */

    /**
     * � ������ ���� b (������������� 4 ����� �����) ���������� �������� ���� b
     * (������������� 1 ����� �����)
     * ��� ��� 5 �� ������� �� ������� ������ �����, 1 ���� ����� = 00000000,
     * �� b ������ ����� ����� 0.
     */
    *p=*(p+3); /* �������� �� ������ p ������ ���� ����� �������� �� ������ p + 3 */

    /**
     * � 4 ���� b (������������� 1 ����� �����) ���������� c, ������� ����� 5.
     * ����������, b � �������� ������ �����:
     * 00000101 00000000 00000000 00000000
     * � ���������� ������: 2 ^ 24 + 2 ^ 26 = 83886080
     */
    *(p+3)=c; /* �������� �� ������ p + 3 ������ ���� ����� c */

    /**
     * ���������:
     * p=0028FED0      c=5     a=0028FED0      b=83886080
     * (��. ���������� ��������������)
     */
    printf("p=%p\tc=%d\ta=%p\tb=%d\n", p, c, a, b);

    /**
     * ��������� x ������ ��������� �� y (0x0028FEC8)
     */
    x = &y; /* � ��������� x ���������� ����� y */

    /**
     * ���������:
     * x=0028FEC8      *x=3.500000     y=3.500000
     * ������ ��� ����� y = 0x0028FEC8,
     * �������� y = 3.5
     */
    printf("x=%p\t*x=%f\ty=%f\n", x, *x, y);
    
    /* ������: a = x; */
    /**
     * �������������� ���������:
     * ������ a ��������� ���� ��, ���� � ��������� x (x ��������� �� ���������� ���������� y).
     * ���������� y ���� float, �� ��������� a - ���� int*, � ������, �� ����� �������������
     * ���������� ���������� y ��� ����� �����.
     * a = 0x0028FEC8
     */
    a = (int*)x;
    
    /**
     * �������� �� ������ a ������ ���� ����� �������� �� ������ x.
     * ��� ��� ��� ��������� a - int*, � ��� ��������� x - float*,
     * ���������� ������� �������������� �����, ������� y (y = 3.5) �������������.
     * �������� �� ��, ��� y - float, � ���� ������������ ������ �������� 3 ��� integer.
     * ���������� � ������ ����� ��������: 00000011 00000000 00000000 00000000
     * �� ����������� �������� ����� ���: 00000000 00000000 00000000 00000011
     * ���� ��������� ���� ��� � ����� � ��������� ������, ��������� 0
     */
    *a = *x;
    
    /* ������:     pintf("a=%p\t*a=%d\tx=%p\t*x=%f\ty=%f\n",
           a, *a, x, *x, y); */
    /**
     * �������: a=0028FEC8      *a=3    x=0028FEC8      *x=0.000000     y=0.000000
     * a=0028FEC8, ������ ��� ����� ������� ���������� - 0x0028FEC8
     * *a = 3, ������ ��� a ���� int*, �������������� ������������ �������� ��� int, 00000011 = 3
     * x=0028FEC8, ������ ��� ����� ������� ����������
     * *x=0.000000 (��. ���������� ���� � �������������)
     * y=0.000000 (��. ���������� ���� � �������������)
     */
    printf("a=%p\t*a=%d\tx=%p\t*x=%f\ty=%f\n",
       a, *a, x, *x, y);

    /**
     * ������ a ��������� �� 0x0028FED0
     */
    a = &b; /* � ��������� a ���������� ����� b */
    
    /* ������: y = 12345,6789; */
    y = 12345.6789;
    
    /**
     * ���������: x=0028FEC8      *x=12345.678711 y=12345.678711
     */
    printf("x=%p\t*x=%f\ty=%f\n", x, *x, y);
    
    /* ������: p = x; */
    /**
     * �������������� ���������:
     * ������ p ��������� ���� ��, ���� � ��������� x (x ��������� �� ���������� ���������� y).
     * ��������� ��������� ������ �����, ��� ��������������� p ��������� ������ ���� ���������� y.
     * p ������ ����� 0x0028FEC8
     */
    p = (char*)x;

    /**
     * ���������� �� ��������� p � �������� �� ���� ��������.
     * ��� �������� = ������ ���� ���������� y, �������� ������� ����� 12345.6789
     */
    c=*p; /* � c ���������� ��������, �� ������� ��������� ��������� p */

    /**
     * � ������ ���� y (������������� 4 ����� �����) ���������� �������� ���� y
     * (������������� 1 ����� ����� � IEEE-754)
     */
    *p=*(p+3); /* �������� �� ������ p ������������� �������� �� ������ p + 3 */

    /**
     * � 4 ���� y (������������� 1 ����� �����) ���������� c.
     * ����������, ���������� ������� 1 ���� � 4 ������ � IEEE-754 �����������.
     * ����: 01000110 01000000 11100110 10110111 = 12345.6789
     * �����: 10110111 01000000 11100110 01000110 = -0.000011497706509544514
     */
    *(p+3)=c; /* �������� �� ������ p + 3 ������������� �������� c */

    /**
     * ���������: p=0028FEC8      c=-73   x=0028FEC8      y=-0.000011
     * p=0028FEC8, ������ ��� 0x0028FEC8 - ����� y
     * c=-73, ������ ��� 10110111 � �������� ������� = -73
     * x=0028FEC8, ������ ��� 0x0028FEC8 - ����� y,
     * y=-0.000011 (��. ���������� �����������)
     */
    printf("p=%p\tc=%d\tx=%p\ty=%f\n", p, c, x, y);

    /**
     * m ������ ��������� �� n
     */
    m = &n;

    /**
     * �������: m=0028FEB8      *m=0.000000     n=0.000000
     * m=0028FEB8, ������ ��� ����� n = 0x0028FEB8
     * *m= �����, ������� �������� �� ������ 0x0028FEB8
     * n= ��� �� ����� �����
     */
    printf("m=%p\t*m=%lf\tn=%lf\n", m, *m, n);

    n = 5.5;

    /**
     * �������: m=0028FEB8      *m=5.500000     n=5.500000
     * m=0028FEB8, ������ ��� ����� n = 0x0028FEB8
     * *m=5.500000, ������ ��� ������ ��� ��������� ��������, �� ������� ���� ��������� ���������, 5.5
     * n=5.500000, ������ ��� ������ ��� ���� ����������
     */
    printf("m=%p\t*m=%lf\tn=%lf\n", m, *m, n);

    /**
     * ������������� ������������.
     * ������ b = 1, n = 1.7, y = 1.7
     */
    b = n = y = 1.7;
    
    /* ������: print("b=%d\ty=%f\tn=%lf\n", b, y, n); */
    /**
     * �������: b=1     y=1.700000      n=1.700000
     * (��. ���������� �����������)
     */
    printf("b=%d\ty=%f\tn=%lf\n", b, y, n);
    
    /**
     * �������: *a=1    *x=1.700000     *m=1.700000
     * ������ ��� a ��������� �� b, x ��������� �� y, m ��������� �� n
     */
    printf("*a=%d\t*x=%f\t*m=%lf\n", *a, *x, *m);

    /**
     * m ��������� �� n (0x0028FEB8)
     */

    /**
     * ����� ���������� �� 2, m ��������� �� 0x0028FEB8 + 0x10 = 0x0028FEC8
     */
    m += 2;
    /**
     * ����� ����������, m ��������� �� 0x0028FEB8 + 0x8 = 0x0028FEC0
     */
    /*m++;*/
    
    /**
     * �������: n=1.700000      n=0028FEB8      m=0028FED0
     * n=1.7, ������ ��� ��� �������� ���� ���������
     * n=0028FEB8, ������ ��� ��� ����������� ����� n.
     * m=0028FED0 (��. ���������� �����������)
     */
    printf("n=%lf\tn=%p\tm=%p\n", n, &n, m);

    /**
     * �� ������ m ������������ 5.0 - 5.5 + 1 = 0.5
     */
    *m = (float)*a - n + (int)*x;

    /**
     * ���������: m=0028FED0      *m=0.300000
     * (��. ���������� �����������)
     */
    printf("m=%p\t*m=%lf\n", m, *m);

    /**
     * ����� ��������.
     */
    printf("Values: p=%p, c=%d, a=%p, b=%d, x=%p, y=%f, m=%p, n=%lf\n", p, c, a, b, x, y, m, n);

    system("pause");
    
    /* ������: return0; */
    return 0;

    /*
    ��� m += 2

     */

}