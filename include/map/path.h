#ifndef PATH_H
#define PATH_H

#include <vector>

#include "include/map/grid.h"

class Path {
  private:
    std::vector<Grid *> path;

  public:
    Path(const std::vector<Grid *> &path);
    std::vector<Grid *> getPath() const;
};

#endif // PATH_H
