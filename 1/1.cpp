#include <iostream>
using namespace std;
const int N = 3, M = 2, M2 = M + N + 1;
class s_fract {
	friend bool fr1_gr_fr2(s_fract fr1, s_fract fr2, bool f);
protected:
	int a, b;
public:
	s_fract(int x, int y);
	void print();
	void sum(s_fract fr1, s_fract fr2);
	void diff(s_fract fr1, s_fract fr2);
	void mult(s_fract fr1, s_fract fr2);
	void div(s_fract fr1, s_fract fr2);
	void red();
	bool eq0();
};
s_fract::s_fract(int x = 0, int y = 1)
{
	if (y > 0)
	{
		a = x;
		b = y;
		red();
	}
	else if (y < 0)
	{
		a = -x;
		b = -y;
		red();
	}
	else
	{
		a = 0;
		b = 0;
	}
}
void s_fract::print()
{
	if ((b != 0) && (b != 1))
		cout << a << "/" << b;
	else if ((b != 0) && (b == 1))
		cout << a;
	else
		cout << INFINITY;
}
void s_fract::sum(s_fract fr1, s_fract fr2)
{
	s_fract obm;
	if ((fr1.b == 0) || (fr2.b == 0))
		return;
	if (fr1.b < fr2.b)
	{
		obm = fr1;
		fr1 = fr2;
		fr2 = obm;
	}

	if (fr1.b == fr2.b)
	{
		a = fr1.a + fr2.a;
		b = fr1.b;
	}
	else if (fr1.b % fr2.b != 0)
	{
		a = fr1.a * fr2.b + fr2.a * fr1.b;
		b = fr1.b * fr2.b;
	}
	else if (fr1.b % fr2.b == 0)
	{
		a = fr1.a + fr2.a * (fr1.b / fr2.b);
		b = fr1.b;
	}
	if (eq0())
		b = 1;
	red();
}
void s_fract::diff(s_fract fr1, s_fract fr2)
{
	fr2.a *= -1;
	sum(fr1, fr2);
}
void s_fract::mult(s_fract fr1, s_fract fr2)
{
	if ((fr1.b == 0) || (fr2.b == 0))
		return;
	a = fr1.a * fr2.a;
	b = fr1.b * fr2.b;
	if (eq0())
		b = 1;
	red();
}
void s_fract::div(s_fract fr1, s_fract fr2)
{
	int obm;
	if ((fr1.b == 0) || (fr2.b == 0))
		return;
	obm = fr2.a;
	fr2.a = fr2.b;
	fr2.b = obm;
	if (fr2.b < 0)
	{
		fr2.a *= -1;
		fr2.b *= -1;
	}
	mult(fr1, fr2);
}
void s_fract::red()
{
	int x, y, obm;
	if ((a == 0) || (b == 0))
		return;
	for (x = abs(a), y = abs(b); x != y; y -= x)
	{
		if (x > y)
		{
			obm = x;
			x = y;
			y = obm;
		}
	}
	a /= x;
	b /= x;
}
bool s_fract::eq0()
{
	if ((a == 0) && (b != 0))
		return true;
	else
		return false;
}



bool fr1_gr_fr2(s_fract fr1, s_fract fr2, bool f = false)
{
	int t;
	if ((fr1.b == 0) || (fr2.b == 0))
		return false;

	if (f)
	{
		fr1.a = abs(fr1.a);
		fr2.a = abs(fr2.a);
	}

	if (((fr1.b > fr2.b) && (fr1.b % fr2.b != 0)) || ((fr1.b <= fr2.b) && (fr2.b % fr1.b != 0)))
	{
		t = fr1.b;
		fr1.a *= fr2.b;
		fr1.b *= fr2.b;
		fr2.a *= t;
		fr2.b *= t;
	}
	else if ((fr1.b > fr2.b) && (fr1.b % fr2.b == 0))
	{
		fr2.a *= (fr1.b / fr2.b);
		fr2.b = fr1.b;
	}
	else if ((fr1.b <= fr2.b) && (fr2.b % fr1.b == 0))
	{
		fr1.a *= (fr2.b / fr1.b);
		fr1.b = fr2.b;
	}

	if (fr1.a > fr2.a)
		return true;
	else
		return false;
}

void print_a(s_fract A[N][M + 1])
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j <= M; j++)
		{
			cout << "\t";
			A[i][j].print();
		}
		cout << endl;
	}
}

void print_tab(s_fract tab[N + 1][M2], int x[N], s_fract s[N] = NULL)
{
	int i, j;
	cout << " б.п.\t|\t1";
	for (i = 1; i < M2; i++)
		cout << "\tx" << i;

	if (s != NULL)
		cout << "\t| СО";

	cout << "\n____________________________________________________________________________\n";
	for (i = 0; i <= N; i++)
	{
		if (i < N)
			cout << " x" << x[i] << "\t|";
		else
			cout << " z\t|";
		for (j = 0; j < M2; j++)
		{
			cout << "\t";
			tab[i][j].print();
		}

		if ((s != NULL) && (i < N))
		{
			cout << "\t| ";
			if (fr1_gr_fr2(s[i], 0))
				s[i].print();
			else
				cout << "-";
		}

		cout << endl;
	}
}

void print_x(int m, s_fract tab[N + 1][M2], int x[N], s_fract l[M] = NULL)
{
	int i, j;
	bool f;
	for (i = 1; i < m; i++)
	{
		f = false;
		for (j = 0; j < N; j++)
		{
			if (i == x[j])
			{
				if (l == NULL)
				{
					cout << " ";
					tab[j][0].print();
				}
				else if (i - 1 < M)
					l[i - 1] = tab[j][0];
				f = true;
				break;
			}
		}
		if (!f)
		{
			if (l == NULL)
				cout << " 0";
			else if (i < M)
				l[i - 1] = s_fract(0);
		}
	}
}

void bas(int i2, int j2, s_fract A[N + 1][M2])
{
	int i, j;
	s_fract t, t2;
	t = A[i2][j2];
	for (j = 0; j < M2; j++)
		A[i2][j].div(A[i2][j], t);
	//cout << "\n (1 в диагонали)\n ~";
	//print_t(A);

	for (i = 0; i <= N; i++)
	{
		if (i == i2)
			continue;
		t.diff(s_fract(0), A[i][j2]);
		for (j = 0; j < M2; j++)
		{
			t2.mult(t, A[i2][j]);
			A[i][j].sum(A[i][j], t2);
		}
	}
	//cout << "\n (нули)\n ~";
	//print_t(A);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int i, j, k = M, c = 1, i2, j2, x[N] = { 1, 2, 3 };
	bool f, g = false;
	s_fract z = s_fract(0), min, tab[N + 1][M2], s[N], l[2][M], p[M] = { /*s_fract(10), s_fract(3)*/ s_fract(-5), s_fract(0) /*s_fract(2), s_fract(-8)*/ }, A[N][M + 1] =
	{
		/*s_fract(2), s_fract(1), s_fract(10),
		s_fract(3), s_fract(4), s_fract(30),
		s_fract(3), s_fract(8), s_fract(42),*/

		s_fract(3), s_fract(-3), s_fract(-2),
		s_fract(4), s_fract(-2), s_fract(-1),
		s_fract(2), s_fract(-3), s_fract(-3),

		/*s_fract(1), s_fract(-4), s_fract(-8),
		s_fract(-2), s_fract(1), s_fract(-4),
		s_fract(1), s_fract(1), s_fract(1),*/
	};
	cout << " z = ";
	for (i = 0; i < M; i++)
	{
		if (!fr1_gr_fr2(0, p[i]) && (i != 0))
			cout << "+";
		p[i].print();
		cout << "x(" << i + 1 << ") ";
	}
	if (!fr1_gr_fr2(0, z))
		cout << "+";
	z.print();
	cout << " -> min" << endl;
	print_a(A);
	cout << endl;

	for (i = 0; i < N; i++)
	{
		tab[i][0] = A[i][M];
		for (j = 0; j < M; j++)
			tab[i][j + 1] = A[i][j];
		for (j = M + 1; j < M2; j++)
		{
			if (j == i + M + 1)
				tab[i][j] = s_fract(-1);
			else
				tab[i][j] = s_fract(0);
		}
	}
	for (i = 0; i < M2; i++)
	{
		tab[N][i] = s_fract(0);
		if ((i > 0) && (i <= M))
			tab[N][i] = p[i - 1];
	}
	tab[N][0] = z;
	for (i = 0; i < N; i++)
		bas(i, x[i], tab);
	print_tab(tab, x);



	while (1)
	{
		cout << "\n\n_______________\n Таблица " << c << endl;
		if (k == M)
			k = 0;
		else
		{
			k = M - k;
			g = true;
		}
		f = true;
		for (i = 1; i < M2; i++)
		{
			if (fr1_gr_fr2(0, tab[N][i]))
				f = false;
			if (!tab[N][i].eq0())
				k++;
		}
		if (f && (k == M))
			break;

		min = s_fract(0);
		if (k == M)
		{
			for (i = 1; i < M2; i++)
			{
				if ((i == 1) || (fr1_gr_fr2(0, tab[N][i]) && fr1_gr_fr2(min, tab[N][i])))
				{
					min = tab[N][i];
					j2 = i;
				}
			}
		}
		else
		{
			for (j2 = 1; j2 < M2; j2++)
			{
				if (!tab[N][j2].eq0())
					continue;
				f = true;
				for (i = 0; i < N; i++)
				{
					if (x[i] == j2)
					{
						f = false;
						break;
					}
				}
				if (f)
					break;
			}
		}
		for (i = 0; i < N; i++)
			s[i].div(tab[i][0], tab[i][j2]);
		print_tab(tab, x, s);

		i2 = -1;
		for (i = 0; i < N; i++)
		{
			if (fr1_gr_fr2(s[i], 0))
			{
				min = s[i];
				i2 = i++;
				break;
			}
		}
		if (i2 == -1)
		{
			cout << " Решений нет.";
			return 0;
		}
		for (; i < N; i++)
		{
			if (fr1_gr_fr2(s[i], 0) && fr1_gr_fr2(min, s[i]))
			{
				min = s[i];
				i2 = i;
			}
		}
		
		cout << " Решающий элемент: (i = " << i2 << ", j = " << j2 << ") ";
		tab[i2][j2].print();
		cout << "\n x" << c << " = (";
		print_x(M2, tab, x);
		cout << " )\n z1 = ";
		tab[N][0].print();

		if (k != M)
			print_x(M2, tab, x, l[0]);
		x[i2] = j2;
		bas(i2, j2, tab);
		c++;
	}



	print_tab(tab, x);
	cout << "\n z(x" << c << ") = z(";
	if (!g)
		print_x(M + 1, tab, x);
	else
	{
		print_x(M2, tab, x, l[1]);
		for (i = 0; i < M; i++)
		{
			cout << " ";
			l[0][i].print();
			z.diff(l[1][i], l[0][i]);
			if (fr1_gr_fr2(z, s_fract(0)))
				cout << "+";
			if (!z.eq0())
			{
				z.print();
				cout << "lam";
			}
		}
	}
	cout << " ) = zmin = ";
	z.mult(tab[N][0], s_fract(-1));
	z.print();
	if (g)
		cout << " (0 <= lam <= 1)";
	return 0;
}