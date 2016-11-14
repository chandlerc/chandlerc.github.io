#include <vector>

int sum(const std::vector<int> &numbers) {
  int result = 0;
  for (std::vector<int>::const_iterator it = numbers.begin();
       it != numbers.end(); ++it) {
    result += *it;
  }
  return result;
}
