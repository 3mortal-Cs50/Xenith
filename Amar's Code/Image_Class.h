/**
 * @File  : Image_Class.h
 * @brief : This file contains the declaration of the Image class.
 *
 * @authors : Shehab Diab, Youssef Mohamed , Nada Ahmed.
 * Dr Mohamed El-Ramely ,
 * @copyright : FCAI Cairo University
 * @version   : v2.0 (Added operator= and copy constructor)
 * @date      : 27/3/2024
 */

// stb_image header definitions
#ifndef _IMAGE_CLASS_H
#define _IMAGE_CLASS_H

#define ll long long
#define PNG_TYPE 1
#define BMP_TYPE 2
#define TGA_TYPE 3
#define JPG_TYPE 4
#define UNSUPPORTED_TYPE -1

// stb_image header definitions
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define pixel unsigned int

#include <iostream>
#include <exception>
#include <string>
#include <string.h>
#include <algorithm> // For std::min/max

/**
 * @class Image
 * @brief Represents an image with functionalities for loading, saving, and manipulating pixels.
 */
class Image
{
private:
    /**
     * @brief Checks if the given filename has a valid extension.
     *
     * @param filename The filename to check.
     * @return True if the filename has a valid extension, false otherwise.
     */
    bool isValidFilename(const std::string &filename)
    {
        const char *extension = strrchr(filename.c_str(), '.');
        if (extension == nullptr)
        {
            std::cerr << "Invalid filename: " << filename << std::endl;
            return false;
        }

        return true;
    }

    /**
     * @brief Determines the image type based on the file extension.
     *
     * @param extension The file extension to determine the type.
     * @return The type of image format.
     */
    short getExtensionType(const char *extension)
    {
        // Simple case-sensitive check based on your original logic
        if (strcmp(extension, ".png") == 0)
        {
            return PNG_TYPE;
        }
        if (strcmp(extension, ".bmp") == 0)
        {
            return BMP_TYPE;
        }
        if (strcmp(extension, ".tga") == 0)
        {
            return TGA_TYPE;
        }
        if (strcmp(extension, ".jpg") == 0 || strcmp(extension, ".jpeg") == 0)
        {
            return JPG_TYPE;
        }

        std::cerr << "Unsupported image format: " << extension << std::endl;
        return UNSUPPORTED_TYPE;
    }

private:
    std::string filename; ///< Stores the filename of the image.

public:
    int width = 0;  ///< Width of the image.
    int height = 0; ///< Height of the image.
    // NOTE: Set default channels to 4 (RGBA) for new images
    int channels = 4;                   ///< Number of color channels in the image (RGBA).
    unsigned char *imageData = nullptr; ///< Pointer to the image data.

    /**
     * @brief Default constructor for the Image class.
     */
    Image() = default;

    /**
     * @brief Constructor that loads an image from the specified filename.
     *
     * @param filename The filename of the image to load.
     */
    Image(std::string filename) : filename((filename))
    {
        loadNewImage(this->filename);
    }

    /**
     * @brief Constructor that creates an image with the specified dimensions.
     *
     * @param mWidth The width of the image.
     * @param mHeight The height of the image.
     */
    Image(int mWidth, int mHeight)
    {
        this->width = mWidth;
        this->height = mHeight;
        // The default channels is 4, so allocate for RGBA
        this->imageData = (unsigned char *)malloc(mWidth * mHeight * this->channels);
        if (this->imageData)
        {
            // Initialize all alpha values to 255 (opaque)
            for (int k = 3; k < mWidth * mHeight * this->channels; k += this->channels)
            {
                this->imageData[k] = 255;
            }
        }
    }

    /**
     * @brief Constructor that creates an image by copying another image.
     *
     * @param other The Image we want to copy.
     */
    Image(const Image &other)
    {
        *this = other;
    }

    /**
     * @brief Overloading the assignment operator.
     *
     * @param image The Image we want to copy.
     *
     * @return *this after copying data.
     */
    Image &operator=(const Image &image)
    {
        if (this == &image)
        {
            return *this;
        }

        stbi_image_free(this->imageData);
        this->imageData = nullptr;

        this->width = image.width;
        this->height = image.height;
        this->channels = image.channels;
        // Use memcpy for efficiency if memory is valid
        if (image.imageData != nullptr)
        {
            size_t data_size = (size_t)width * height * channels;
            imageData = (unsigned char *)malloc(data_size);
            if (imageData)
            {
                memcpy(imageData, image.imageData, data_size);
            }
        }

        return *this;
    }

    /**
     * @brief Destructor for the Image class.
     */
    ~Image()
    {
        if (imageData != nullptr)
        {
            stbi_image_free(imageData);
        }
        this->width = 0;
        this->height = 0;
        this->channels = 0; // Reset channels as well
        this->imageData = nullptr;
    }

    /**
     * @brief Loads a new image from the specified filename.
     *
     * @param filename The filename of the image to load.
     * @return True if the image is loaded successfully, false otherwise.
     * @throws std::invalid_argument If the filename or file format is invalid.
     */
    bool loadNewImage(const std::string &filename)
    {
        if (!isValidFilename(filename))
        {
            std::cerr << "Couldn't Load Image" << '\n';
            throw std::invalid_argument("The file extension does not exist");
        }

        const char *extension = strrchr(filename.c_str(), '.');
        short extensionType = getExtensionType(extension);
        if (extensionType == UNSUPPORTED_TYPE)
        {
            std::cerr << "Unsupported File Format" << '\n';
            throw std::invalid_argument("File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported");
        }
        if (imageData != nullptr)
        {
            stbi_image_free(imageData);
        }

        int original_channels;
        // NOTE: Request 4 channels (STBI_rgb_alpha) to ensure Alpha is always loaded or initialized to 255.
        imageData = stbi_load(filename.c_str(), &width, &height, &original_channels, STBI_rgb_alpha);
        this->channels = STBI_rgb_alpha; // Force channels to 4 (RGBA)

        if (imageData == nullptr)
        {
            std::cerr << "File Doesn't Exist: " << stbi_failure_reason() << '\n';
            throw std::invalid_argument("Invalid filename, File Does not Exist");
        }

        return true;
    }

    /**
     * @brief Saves the image to the specified output filename.
     *
     * @param outputFilename The filename to save the image.
     * @return True if the image is saved successfully, false otherwise.
     * @throws std::invalid_argument If the output filename or file format is invalid.
     */
    bool saveImage(const std::string &outputFilename)
    {
        if (!isValidFilename(outputFilename))
        {
            std::cerr << "Not Supported Format" << '\n';
            throw std::invalid_argument("The file extension does not exist");
        }

        // Determine image type based on filename extension
        const char *extension = strrchr(outputFilename.c_str(), '.');
        short extensionType = getExtensionType(extension);
        if (extensionType == UNSUPPORTED_TYPE)
        {
            std::cerr << "File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported" << '\n';
            throw std::invalid_argument("File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported");
        }

        // Use the actual channel count (should be 4) and stride
        int output_channels = this->channels;
        int stride = width * output_channels;

        if (extensionType == PNG_TYPE)
        {
            // PNG fully supports RGBA
            stbi_write_png(outputFilename.c_str(), width, height, output_channels, imageData, stride);
        }
        else if (extensionType == BMP_TYPE)
        {
            // BMP supports RGBA if output_channels is 4
            stbi_write_bmp(outputFilename.c_str(), width, height, output_channels, imageData);
        }
        else if (extensionType == TGA_TYPE)
        {
            // TGA supports RGBA if output_channels is 4
            stbi_write_tga(outputFilename.c_str(), width, height, output_channels, imageData);
        }
        else if (extensionType == JPG_TYPE)
        {
            // JPG does not support alpha. stbi_write_jpg ignores channel 4 if input is 4-channel.
            stbi_write_jpg(outputFilename.c_str(), width, height, output_channels, imageData, 90);
        }

        return true;
    }

    /**
     * @brief Gets the pixel value at the specified position and channel.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param c The color channel index (0=R, 1=G, 2=B, 3=A).
     * @return Reference to the pixel value.
     * @throws std::out_of_range If the coordinates or channel index is out of bounds.
     */
    unsigned char &getPixel(int x, int y, int c)
    {
        // Call const version for bounds checking
        return const_cast<unsigned char &>(static_cast<const Image &>(*this).getPixel(x, y, c));
    }

    /**
     * @brief Const version of getPixel.
     */
    const unsigned char &getPixel(int x, int y, int c) const
    {
        if (x >= width || x < 0)
        {
            std::cerr << "Out of width bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed width value");
        }
        if (y >= height || y < 0)
        {
            std::cerr << "Out of height bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed height value");
        }
        // NOTE: Bounds check updated to c >= channels (allows 0, 1, 2, 3)
        if (c < 0 || c >= channels)
        {
            std::cerr << "Out of channels bounds. Max channel index is " << channels - 1 << '\n';
            throw std::out_of_range("Out of bounds, Channel index must be less than " + std::to_string(channels));
        }

        return imageData[(y * width + x) * channels + c];
    }

    /**
     * @brief Sets the pixel value at the specified position and channel.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param c The color channel index (0=R, 1=G, 2=B, 3=A).
     * @param value The new value to set.
     * @throws std::out_of_range If the coordinates or channel index is out of bounds.
     */
    void setPixel(int x, int y, int c, unsigned char value)
    {
        // Use the non-const getPixel to perform bounds check and get a writable reference
        getPixel(x, y, c) = value;
    }

    /**
     * @brief Overloaded function call operator for direct pixel access.
     *
     * @param row The row index of the pixel.
     * @param col The column index of the pixel.
     * @param channel The color channel index (0=R, 1=G, 2=B, 3=A).
     * @return Reference to the pixel value.
     */
    unsigned char &operator()(int row, int col, int channel)
    {
        return getPixel(row, col, channel);
    }

    /**
     * @brief Const overloaded function call operator for direct pixel access.
     *
     * @param row The row index of the pixel.
     * @param col The column index of the pixel.
     * @param channel The color channel index (0=R, 1=G, 2=B, 3=A).
     * @return Const reference to the pixel value.
     */
    const unsigned char &operator()(int row, int col, int channel) const
    {
        return getPixel(row, col, channel);
    }

    /**
     * @brief Overloaded function call operator for weighted pixel access (blending).
     *
     * @param x The x-coordinate (row).
     * @param y The y-coordinate (col).
     * @param c The color channel index (0=R, 1=G, 2=B, 3=A).
     * @param blend_factor The weight (0.0 to 1.0) to multiply the pixel value by.
     * @return The calculated weighted pixel value (unsigned char).
     * @throws std::out_of_range If coordinates or channel index is out of bounds.
     */
    unsigned char operator()(int x, int y, int c, float blend_factor) const
    {
        // Use the three-argument const operator() for bounds-checked value retrieval
        unsigned char original_value = (*this)(x, y, c);

        // Perform the weighted calculation
        float result_float = (float)original_value * blend_factor;

        // Clamp and cast back to unsigned char
        return (unsigned char)std::max(0.0f, std::min(255.0f, result_float));
    }
};

#endif // _IMAGE_CLASS_H