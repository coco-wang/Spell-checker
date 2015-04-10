#include <algorithm>
#include <iostream>
using namespace std;
using namespace cop4530;

template <typename T>
HashTable<T>::HashTable(size_t size):currentsize(0)
{
 theTable.resize(prime_below(size));
}

template <typename T>
HashTable<T>::~HashTable()
{
    clear();
}

template <typename T>
void HashTable<T>::clear()
{
      makeEmpty();
}

template <typename T>
bool HashTable<T>::contains(const T& x)
{
    auto& whichlist = theTable[myhash(x)];
    return find(whichlist.begin(),whichlist.end(),x)!=whichlist.end();
}

template <typename T>
void HashTable<T>::rehash()
{
    vector<list<T>> newtable(prime_below(2*currentsize));
    for(int i=0;i<theTable.size();i++)
        newtable.push_back(move(theTable[i]));
    swap(newtable, theTable);
}

template <typename T>
bool HashTable<T>::write_to_file(const char* filename)
{
    ofstream out(filename);
    streambuf* coutbuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());
    return true;
}
template <typename T>
bool HashTable<T>::load(const char* filename)
{
   ifstream file(filename);
   string line;
   while (getline(file,line)){
        istringstream iss(line);
        T x;
        iss>>x;
        insert(x);
   }
}

template <typename T>
bool HashTable<T>::insert(const T& x)
{
    auto& whichlist = theTable[myhash(x)];
    if(contains(x))
        return false;
    whichlist.push_back(x);
    ++currentsize;
    if (currentsize>theTable.size())
        rehash();
    return true;
}
bool HashTable<T>::insert(T && x)
{
auto& whichlist = theTable[myhash(x)];
if (contains(x))
    return false;
whichlist.push_back(std::move(x));
++currentsize;
if (currentsize>theTable.size())
        rehash();
}

template <typename T>
bool HashTable<T>::remove(const T& x)
{
    if (!contains(x))
        return false;
    auto& whichlist = theTable[myhash(x)];
    auto itr = find(whichlist.begin(),whichlist.end(),x);
    whichlist.erase(itr);
    --currentsize;
    return true;
}

template <typename T>
void HashTable<T>::makeEmpty()
{
   if (currentsize ==0)
            return;
   for (int i=0; i<theTable.size();i++)
            theTable[i].clear();
}

template <typename T>
size_t  HashTable<T>::myhash(const T& x)
{
static hash<T> hf;
return hf(x)% theTable.size();
}

template <typename T>
void HashTable<T>::dump()
{
if (currentsize!=0)
    {
     for (auto& whichlist:theTable)
        {
         for (auto itr=whichlist.begin();itr!=whichlist.end();++itr)
            cout << *itr<<endl;
        }
    }
}
template <typename T>
unsigned long HashTable<T>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
                std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
        return n;
      --n;
    }

  return 2
  }
  template <typename T>
void HashTable<T>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }

}


  
  
