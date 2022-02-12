//
// Created by Kaeden Cameron
// 1,334 LoC (01/31/22)
//

#include "src/Model.h"

int main()
{
    // Assemble data
    Data dataset;
    dataset.initializeData("data/iris.data", 3);
    Matrix input = dataset.data;
    Matrix answer = dataset.answers;

    // Create model
    Model model(3, {5, 3, 3}, {0, 0, 0, 0});

    // Train model
    model.train_model(input, answer, 20000, 4);

    // Test model
    model.run_model(input);
    answer = transpose(answer);
    printMatrix(answer);
}
