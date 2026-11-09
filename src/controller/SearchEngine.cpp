#include "SearchEngine.h"
#include <algorithm>
#include <cctype>

namespace library {
namespace {
std::string lower(std::string s){std::transform(s.begin(),s.end(),s.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});return s;}
std::string text(const LibraryItem& i,SearchField f){switch(f){case SearchField::Title:return i.title();case SearchField::Author:return i.author();case SearchField::Type:return toString(i.type());}return {};}
std::string sortText(const LibraryItem& i,SortField f){switch(f){case SortField::Title:return lower(i.title());case SortField::Author:return lower(i.author());case SortField::Year:return std::to_string(i.year());}return {};}
bool less(const std::shared_ptr<LibraryItem>& a,const std::shared_ptr<LibraryItem>& b,SortField f){if(f==SortField::Year)return a->year()<b->year();return sortText(*a,f)<sortText(*b,f);}
void recursiveSearch(const SearchEngine::Items& a,const std::string& q,SearchField f,size_t i,SearchEngine::Items& out){if(i>=a.size())return;if(lower(text(*a[i],f)).find(q)!=std::string::npos)out.push_back(a[i]);recursiveSearch(a,q,f,i+1,out);}
void selection(SearchEngine::Items& a,SortField f){for(size_t i=0;i<a.size();++i){size_t m=i;for(size_t j=i+1;j<a.size();++j)if(less(a[j],a[m],f))m=j;std::swap(a[i],a[m]);}}
void insertion(SearchEngine::Items& a,SortField f){for(size_t i=1;i<a.size();++i){auto x=a[i];size_t j=i;while(j>0&&less(x,a[j-1],f)){a[j]=a[j-1];--j;}a[j]=x;}}
void mergeSort(SearchEngine::Items& a,SortField f){if(a.size()<2)return;size_t m=a.size()/2;SearchEngine::Items l(a.begin(),a.begin()+static_cast<std::ptrdiff_t>(m)),r(a.begin()+static_cast<std::ptrdiff_t>(m),a.end());mergeSort(l,f);mergeSort(r,f);size_t i=0,j=0,k=0;while(i<l.size()&&j<r.size())a[k++]=less(r[j],l[i],f)?r[j++]:l[i++];while(i<l.size())a[k++]=l[i++];while(j<r.size())a[k++]=r[j++];}
void quick(SearchEngine::Items& a,SortField f,int lo,int hi){if(lo>=hi)return;auto pivot=a[static_cast<size_t>(hi)];int i=lo;for(int j=lo;j<hi;++j)if(!less(pivot,a[static_cast<size_t>(j)],f))std::swap(a[static_cast<size_t>(i++)],a[static_cast<size_t>(j)]);std::swap(a[static_cast<size_t>(i)],a[static_cast<size_t>(hi)]);quick(a,f,lo,i-1);quick(a,f,i+1,hi);}
}
SearchEngine::Items SearchEngine::search(const Items& source,const std::string& query,SearchField field,SearchStrategy strategy){Items result;if(query.empty())return result;std::string q=lower(query);if(strategy==SearchStrategy::Binary){Items ordered=source;std::stable_sort(ordered.begin(),ordered.end(),[&](auto& a,auto& b){return lower(text(*a,field))<lower(text(*b,field));});int lo=0,hi=static_cast<int>(ordered.size())-1;while(lo<=hi){int mid=lo+(hi-lo)/2;std::string v=lower(text(*ordered[static_cast<size_t>(mid)],field));if(v==q){result.push_back(ordered[static_cast<size_t>(mid)]);break;}if(v<q)lo=mid+1;else hi=mid-1;}return result;}if(strategy==SearchStrategy::Recursive)recursiveSearch(source,q,field,0,result);else for(auto& i:source)if(lower(text(*i,field)).find(q)!=std::string::npos)result.push_back(i);return result;}
SearchEngine::Items SearchEngine::sort(const Items& source,SortField field,SortAlgorithm algorithm){Items a=source;switch(algorithm){case SortAlgorithm::Selection:selection(a,field);break;case SortAlgorithm::Insertion:insertion(a,field);break;case SortAlgorithm::Merge:mergeSort(a,field);break;case SortAlgorithm::Quick:quick(a,field,0,static_cast<int>(a.size())-1);break;}return a;}
std::string SearchEngine::label(SearchField f){switch(f){case SearchField::Title:return "Title";case SearchField::Author:return "Author";case SearchField::Type:return "Type";}return "Title";}
std::string SearchEngine::label(SortField f){switch(f){case SortField::Title:return "Title";case SortField::Author:return "Author";case SortField::Year:return "Year";}return "Title";}
std::string SearchEngine::label(SortAlgorithm a){switch(a){case SortAlgorithm::Selection:return "Selection";case SortAlgorithm::Insertion:return "Insertion";case SortAlgorithm::Merge:return "Merge";case SortAlgorithm::Quick:return "Quick";}return "Merge";}
}
