# PUNKS: A Line Follower and Maze Solver Robot

### IEEE FST Robots 3.0: Survey Corps Challenge, AerobotiX INSAT Club

**Skills and technologies used:** C++, Arduino, SOLIDWORKS, PID Control, Encoder Reading, Sampling, Odometry, Ultrasonic Sensing, IR tracking, ISR

## Introduction

The Line Follower and Maze Solver Robot project, developed under the IEEE FST Robots 3.0 competition in the Survey Corps Challenge in collaboration with AerobotiX INSAT Club, showcases innovative engineering solutions to navigate predefined paths autonomously. Leveraging a combination of hardware and software technologies, this project aims to efficiently tackle the challenges posed by line-following and maze-solving tasks.

## Key Features

- Autonomous line-following capabilities with an adaptive algorithm for path optimization.
- Efficient maze traversal using a high-performance velocity PID controller and ultrasonic sensors.
- Integration of interrupt service routines (ISRs) for precise encoder readings and control.

## Project Overview

In a collaborative effort involving 4 colleagues, the project was conceptualized and executed within a tight deadline of 3 days. Each team member played a crucial role in critical design decisions, sensor selection, assembly, and programming, ensuring the successful realization of the robot.

## Technical Details

- **Adaptive Line Following**: Developed an adaptive algorithm utilizing IR sensor readings to optimize navigation actions, achieving an impressive 94% path-following accuracy across various scenarios.
- **High-Performance Velocity PID Controller**: Implemented a robust PID controller with interrupt service routines to process encoder readings, resulting in significant speed enhancements during straight-line segments, leading to a 35% reduction in mission time.
- **Precise Maze Traversal**: Utilized a PD controller in conjunction with ultrasonic sensors to optimize maze traversal while maintaining a precise 1 cm wall-following distance.

## Getting Started

### Installation

1. Ensure all hardware components are properly assembled as per the provided documentation.
2. Upload the Arduino code onto the microcontroller.
3. Calibrate sensors and fine-tune PID parameters as necessary for optimal performance.

### Usage

1. Place the robot on the designated starting point of the track or maze.
2. Power on the robot and observe its autonomous navigation through the predefined path.
3. Monitor performance and make adjustments as needed to achieve desired results.

## Contributing

Contributions to further enhance the capabilities and performance of this project are welcome.

## License

This project is licensed under the [GPL-3.0 License](LICENSE).

## Contact

For inquiries or feedback, please contact:

- Elyes Khechine: elyeskhechine@gmail.com
