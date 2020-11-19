#include "GenCustomHierarchy.h"
#include "Classes.h"

int main() {
  GenCustomHierarchy<TypeList<
          TypeNumber1, TypeNumber2, TypeNumber3, TypeNumber4, TypeNumber5,
          TypeNumber6, TypeNumber7, TypeNumber8, TypeNumber9, TypeNumber10,
          TypeNumber11, TypeNumber12, TypeNumber13, TypeNumber14, TypeNumber15,
          TypeNumber16, TypeNumber17, TypeNumber18, TypeNumber19, TypeNumber20,
          TypeNumber21, TypeNumber22, TypeNumber23, TypeNumber24>,
          Holder> hierarchy;
}

