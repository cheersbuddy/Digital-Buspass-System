# Digital Bus Pass System

## Abstract
The Smart Card Bus Pass project seeks to revolutionize conventional bus passes through the integration of smart card technology. These cards promise to enhance the passenger journey by offering convenience, security, and efficient payment methods. By simplifying boarding procedures and eliminating cash transactions, the system aims to bolster overall operational efficiency. Moreover, the incorporation of smart cards will yield valuable data insights, facilitating the optimization of public transportation routes and schedules. With seamless integration, reduced operational costs, and a transition towards digital transactions, this initiative pledges to modernize and enhance the effectiveness of public transportation systems.

## Problem Statement
During peak hours, passengers encounter difficulties boarding buses and having their bus passes promptly checked, leading to delays and frustration. This bottleneck arises due to the sheer volume of commuters and the manual process of pass verification, resulting in lengthy queues and overcrowded buses. Passengers often struggle to navigate through crowds, making boarding time-consuming and stressful. Additionally, manual pass verification slows down boarding, exacerbating congestion and increasing travel time for all passengers. These challenges underscore the necessity for an automated, streamlined system to improve boarding experiences and ensure swift pass verification during peak hours.

## Proposed Solution
The Digital Bus Pass System harnesses the power of smart card technology to replace traditional paper tickets with digital passes stored on RFID cards. This initiative aims to revolutionize traditional bus pass systems by streamlining boarding processes, reducing congestion, and enhancing the overall passenger experience. With real-time updates and remote management capabilities, this project represents a significant step towards creating a more efficient, accessible, and sustainable mode of public transportation.

## System Features
- **Contactless Card Readers**: Passengers can board buses using RFID smart cards, which are scanned upon entry.
- **Real-Time Updates**: The system provides real-time updates and notifications to passengers and inspectors.
- **Remote Management**: Allows for remote management of card data and system updates.
- **Data Insights**: Collects valuable data to optimize transportation routes and schedules.
- **Security**: Enhances security by eliminating cash transactions and providing secure digital verification.

## Technology Stack
- **Arduino IDE**: Used for programming the microcontroller.
- **EEPROM**: For storing data persistently.
- **LED Indicators & Buzzer**: Indicate pass verification status.
- **GSM Module**: For sending notifications.
- **Arduino Uno**: The microcontroller board used for prototyping.
- **MFRC522 RFID Reader**: For reading RFID cards.

## Prototype Demonstration
In this video, I walk you through the innovative features of the Digital Bus Pass System, showcasing how it revolutionizes the way passengers access and use public transit. From contactless card readers to seamless smartphone integration, our system offers a convenient, efficient, and eco-friendly alternative to traditional paper bus passes. 

- ![image](https://github.com/cheersbuddy/Digital-Buspass-System/assets/126586644/aab7cc17-c378-4d70-8862-338a94a1a50c)

[Watch Prototype Demo](https://drive.google.com/file/d/1lsjDi0Qno4096gIzuJuA-XMTGFve_1kI/view)

## Notifications

- ![image](https://github.com/cheersbuddy/Digital-Buspass-System/assets/126586644/0aaa1cd9-b491-47be-bc79-3553c55fb518)

- **Access Denied**: When an invalid card is scanned or the access limit per day is exceeded, it is indicated with a red LED, a long buzzer sound, and a notification to the user.
- ![image](https://github.com/cheersbuddy/Digital-Buspass-System/assets/126586644/36be3e99-1ba3-4bfc-89a9-992a4f317f30)

- **Access Granted**: When a valid card is scanned, it is indicated by a green LED, a buzzer sound, and a notification is sent to the user.
- ![image](https://github.com/cheersbuddy/Digital-Buspass-System/assets/126586644/44511012-3422-49ef-8ee5-0011b7d17cff)

## Real-World Application
This system aims to modernize public transportation by enhancing passenger convenience and operational efficiency. It provides a scalable solution that can be implemented in urban transit systems globally, contributing to a smarter, more sustainable future in urban transportation.

## Skills Utilized
- **Arduino IDE**
- **Embedded Systems**
- **Hardware Prototyping**

Join us as we embark on a journey towards a smarter future in urban transit with the Digital Bus Pass System.
