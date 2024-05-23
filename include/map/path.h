#ifndef PATH_H
#define PATH_H

#include "grid.h"
#include <vector>

class Path {
  private:
    std::vector<Grid *> path;

  public:
    Path(const std::vector<Grid *> &path);
    std::vector<Grid *> getPath() const;
};

#endif // PATH_H