import cv2
import numpy as np

def adjust_brightness_contrast(image, brightness=0, contrast=1.0):
    # brightness and contrast values are expected in the range of [0, 99]
    alpha = (contrast + 100) / 100.0
    beta = brightness - 50  # shift to be in the range of [-50, 49]

    adjusted_image = cv2.addWeighted(image, alpha, image, 0, beta)
    return adjusted_image

# Read the grayscale image
image_path = 'Dynamic Programming\\Python\\tinyhouse.png'  # Replace with the path to your image
gray_image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

# Set the desired values for brightness and contrast (within the range of [0, 99])
brightness = 45  # Adjust as needed
contrast = 45  # Adjust as needed

# Adjust the brightness and contrast using cv2.addWeighted
adjusted_image = adjust_brightness_contrast(gray_image, brightness=brightness, contrast=contrast)

# Display the original and adjusted images
cv2.imshow('Original Image', gray_image)
cv2.imshow('Adjusted Image', adjusted_image)

# Wait for a key press and then close the windows
cv2.waitKey(0)
cv2.destroyAllWindows()
