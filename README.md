# Xenith: Baby Filter Photoshop
## 🌟 Project Overview
#### Xenith is a minimal, C++-based image manipulation library designed to offer essential "filter Photoshop" capabilities. It is built upon the robust, public-domain stb_image family of libraries, ensuring high-performance and dependency-free file loading and saving.

#### Target Audience: Developers needing quick, functional, and easy-to-understand image transformation tools within a C++ environment.

## Key Features
RGBA Support: Loads and processes images with 4 channels (Red, Green, Blue, Alpha) by default.

Intuitive Pixel Access: Uses overloaded C++ operators for direct Read/Write (R/W) access and weighted blending.

Broad File I/O: Supports PNG, JPEG, BMP, and TGA formats via stb_image.

## 🚀 Getting Started
Installation
Since Xenith is built as a single-header library, integration is simple:

Ensure you have a C++ compiler that supports C++11 or later.

Place Image_Class.h in your project directory.

The necessary stb_image.h and stb_image_write.h libraries are included and implemented directly within Image_Class.h.
### Basic Usage Example  [x]🔨
```

#include <iostream>
#include "Image_Class.h"

// Assuming FlipH is defined elsewhere or in your header
Image FlipH(Image img); 

int main() {
    try {
        // Load an image. It will be internally converted to 4-channel RGBA.
        Image original_img("landscape.jpg");

        std::cout << "Image loaded: " << original_img.width << "x" << original_img.height 
                  << ", Channels: " << original_img.channels << "\n";

        // Apply a filter 
        Image flipped_img = FlipH(original_img);

        // Save the result (PNG is recommended for preserving 4 channels)
        flipped_img.saveImage("output_flipped.png");
        std::cout << "Image saved successfully.\n";

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    return 0;
}
```
