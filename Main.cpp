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
    Model model(2, {8, 3}, {0, 0, 0, 0});

    // Train model
    model.train_model(input, answer, 20000, 50);

    // Test model
    model.run_model({5.4,3.4,1.7,0.2}); // 1
    model.run_model({5.8,2.7,3.9,1.2}); // 2
    model.run_model({5.7,2.5,5.0,2.0}); // 3
}
