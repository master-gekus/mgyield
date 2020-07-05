#include <iostream>
#include <iomanip>

#include <clocale>
#include <gtest/gtest.h>

#include "mgyield.h"

int main(int argc, char** argv)
{
  auto p = new ::mg::yield();

  ::testing::InitGoogleTest(&argc, argv);

#if defined(__MINGW32__)
  std::setlocale(LC_ALL, "Russian");
#elif defined(_WIN32)
  std::setlocale(LC_ALL, "ru-RU");
#else
  std::setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

  delete p;

  return RUN_ALL_TESTS();
}