#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// define a class to represent a 2D point with a class label
class Point {
public:
    double x;
    double y;
    int label;

    Point(double x, double y, int label) : x(x), y(y), label(label) {}

    // calculate the Euclidean distance between this point and another point
    double distance(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

// define a class to represent a k-NN classifier
class KNN {
private:
    int k;
    vector<Point> data;

public:
    KNN(int k) : k(k) {}

    // add a new training example to the classifier
    void add_example(const Point& example) {
        data.push_back(example);
    }

    // make a prediction for a new point
    int predict(const Point& point) const {
        // find the k nearest neighbors of the new point
        vector<pair<double, int>> distances;
        for (const Point& example : data) {
            double distance = point.distance(example);
            distances.push_back(make_pair(distance, example.label));
        }
        sort(distances.begin(), distances.end());

        // count the number of occurrences of each class label among the k nearest neighbors
        vector<int> counts(2);
        for (int i = 0; i < k; i++) {
            cout << '(' << distances[i].first << ',' << distances[i].second << ')';

            int label = distances[i].second;
            counts[label]++;
        }

        // return the most common class label among the k nearest neighbors
        if (counts[0] > counts[1]) {
            return 0;
        } else {
            return 1;
        }
    }
};

int main() {
    // create a k-NN classifier with k=3
    KNN knn(2);

    // add some training examples to the classifier
    knn.add_example(Point(0, 0, 0));
    knn.add_example(Point(1, 1, 1));
    knn.add_example(Point(1, 1, 1));
    knn.add_example(Point(0, 0, 0));
    knn.add_example(Point(1, 1, 1));

    // trolling
    knn.add_example(Point(1, 1, 0));
    knn.add_example(Point(1, 1, 2));
    knn.add_example(Point(2, 2, 2));

    // make a prediction for a new point
    Point point(1, 1, 0); // label is unused for .predict
    int prediction = knn.predict(point);
    cout << "Prediction: " << prediction << endl;

    return 0;
}

/*

0

*/