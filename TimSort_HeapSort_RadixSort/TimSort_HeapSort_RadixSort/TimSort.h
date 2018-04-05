#pragma once
#include "Sort.h"
#include "ctime"
#include "iostream"
using namespace std;

class TimSort: public Sort
{
private:
	int RUN;

private:
	//����������� ����� ������������������
	int GetMinrun(int *nn)
	{
		int r = 0, n = *nn; //������ 1 ���� ����� ��������� ����� ����� ���� �� 1 ��������� 	
		while (n >= 64)
		{
			r |= n & 1; //������� ��������� �, ����� ��� � ����������� �
			n >>= 1; //���� ������� ������� �� 2
		}
		return n + r;
	}

	// ����� ����������� ���������
	void insertionSort(int arr[], int left, int right)
	{
		for (int i = left + 1; i <= right; i++)
		{
			int temp = arr[i];
			int j = i - 1;
			while ((arr[j] > temp) && (j >= left))
			{
				NumComp++;
				arr[j + 1] = arr[j];
				j--;
				arr[j + 1] = temp;
				NumSwaps++;
			}
		}
	}

	//�������
	void merge(int arr[], int l, int m, int r)
	{
		int len1 = m - l + 1, len2 = r - m;
		int *left = new int[m - l + 1], *right = new int[r - m];
		for (int i = 0; i < len1; i++)
			left[i] = arr[l + i];
		for (int i = 0; i < len2; i++)
			right[i] = arr[m + 1 + i];

		int i = 0;
		int j = 0;
		int k = l;
		while (i < len1 && j < len2)
		{
			if (left[i] <= right[j])
			{
				arr[k] = left[i];
				i++;

			}
			else
			{
				arr[k] = right[j];
				j++;
			}
			
			NumComp++;
			k++;
		}

		while (i < len1)
		{
			arr[k] = left[i];
			k++;
			i++;
		}

		while (j < len2)
		{
			arr[k] = right[j];
			k++;
			j++;
		}
		delete[] left;
		delete[] right;
	}

public:
	unsigned int MetodSort(int arr[], int *n)
	{
		NumComp = 0; NumSwaps = 0;
		unsigned int time = clock();
		RUN = GetMinrun(n);
		//cout << "MinRUN = " << RUN << endl;
		for (int i = 0; i < *n; i += RUN)
		{
			if ((i + RUN - 1) < (*n - 1))	insertionSort(arr, i, (i + RUN - 1));
			else	insertionSort(arr, i, (*n - 1));
		}

		int left, right, mid;
		for (int size = RUN; size < *n; size = 2 * size)
		{
			for (left = 0; left < *n; left += 2 * size)
			{
				mid = left + size - 1;
				if ((left + 2 * size - 1) < (*n - 1)) right = left + 2 * size - 1;
				else right = *n - 1;

				merge(arr, left, mid, right);
			}
		}
		return clock() - time;
	}
};
