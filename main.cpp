#include <iostream>
#include <vector>
#include <cmath>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

// Define constants
const int num_blades = 2;        // Number of propeller blades
const double radius = 1.0;      // Radius of the propeller (meters)
const double rpm = 2500.0;      // Rotational speed (revolutions per minute)
const double chord_length = 0.1; // Chord length of the blade (meters)
const double alpha = 5.0;       // Angle of attack (degrees)

int main() {
    // Convert RPM to rad/s
    const double omega = 2.0 * 3.14 * rpm / 60.0;

    // Number of radial sections or elements
    const int num_sections = 20;

    // Initialize vectors to store results
    std::vector<double> r(num_sections);           // Radial positions
    std::vector<double> lift_distribution(num_sections, 0.0);  // Lift distribution

    // Blade Element Method
    for (int i = 0; i < num_sections; ++i) {
        double local_radius = (radius / num_sections) * (i + 0.5);
        double local_velocity = omega * local_radius;
        double local_angle_of_attack = alpha;  // Simplified, assuming constant angle of attack

        // Calculate lift using a basic lift equation (simplified)
        double lift = 0.5 * chord_length * local_velocity * local_velocity * sin(local_angle_of_attack * 3.14 / 180.0);

        // Distribute the lift equally among the blades
        double total_lift = num_blades * lift;

        lift_distribution[i] = total_lift;
    }

    // Display the span-wise distribution of lift
    std::cout << "Span-wise Distribution of Lift:" << std::endl;
    for (int i = 0; i < num_sections; ++i) {
        std::cout << "Radial Position (m): " << r[i] << ", Lift (N): " << lift_distribution[i] << std::endl;
    }


    // Plot the span-wise distribution of lift
    plt::plot(r, lift_distribution);
    plt::title("Span-wise Distribution of Lift");
    plt::xlabel("Radial Position (m)");
    plt::ylabel("Lift (N)");
    plt::grid(true);
    plt::show();

    return 0;
}