#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> GetPrimeNumbers()
{
  ifstream file;
  file.open("prime_numbers.txt");
  string number;
  vector<int> prime_numbers;

  if (file.is_open()) {
    while (getline(file, number)) prime_numbers.push_back(stoi(number));
  } else {
    cout << "Can't open prime_numbers.txt file" << endl;
  }

  return prime_numbers;
}

bool IsPrime(const vector<int>& a, const int& s, const int& t)
{
  // Using binary search
  int l {0}, r {s-1}, m {};
  while (l != r) {
    m = (l + r)/2;
    if (a[m] < t) l = m+1;
    else r = m;
  }

  if (a[r] == t) return true;
  return false;
}

void TheSieveOfEratosthenes(vector<bool>& prime_numbers, const int& n)
{
  prime_numbers[0] = false;
  prime_numbers[1] = false;

  for (int i = 2; i < sqrt(n); ++i) {
    if (prime_numbers[i]) {
      for (int j = i*i; j < n; j += i) prime_numbers[j] = false;
    }
  }
}

void PrimeFactorization(const vector<int>& prime_numbers,
                        vector<int>& factors,
                        const int n)
{
  if (IsPrime(prime_numbers, prime_numbers.size(), n)) {
    factors.push_back(n);
    return;
  }

  for (int i : prime_numbers) {
    if (n % i == 0) {
      factors.push_back(i);
      PrimeFactorization(prime_numbers, factors, n / i);
      return;
    }
  }
}

int main(void)
{
  vector<int> factors;
  vector<int> prime_numbers = GetPrimeNumbers();
  cout << "Finding factors of a positive integer" << endl;
  cout << "Enter a number: ";
  int n {};
  cin >> n;

  if (IsPrime(prime_numbers, prime_numbers.size(), n)) {
    cout << n << " is a prime number" << endl;
  } else {
    PrimeFactorization(prime_numbers, factors, n);

    cout << "Factors of " << n << ":";
    for (int n : factors) cout << " " << n;
    cout << endl;
  }

  return 0;
}
