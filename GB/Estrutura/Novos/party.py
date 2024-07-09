import cv2
import numpy as np
 
filters = [
    {'name': 'Canny', 'function': lambda frame: cv2.Canny(frame, 50, 100)},
    {'name': 'GaussianBlur', 'function': lambda frame: cv2.GaussianBlur(frame, (15, 15), 0)},
    {'name': 'Sobel', 'function': lambda frame: cv2.Sobel(frame, cv2.CV_64F, 1, 0, ksize=5)},
    {'name': 'Laplacian', 'function': lambda frame: cv2.Laplacian(frame, cv2.CV_64F)},
    {'name': 'Magenta', 'function': lambda frame: apply_magenta(frame)},
    {'name': 'EqualizeHist', 'function': lambda frame: cv2.equalizeHist(cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY))},
    {'name': 'Threshold', 'function': lambda frame: cv2.threshold(cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY), 127, 255, cv2.THRESH_BINARY)[1]},
    {'name': 'Erosion', 'function': lambda frame: cv2.erode(frame, np.ones((5, 5), np.uint8), iterations=1)},
    {'name': 'Dilation', 'function': lambda frame: cv2.dilate(frame, np.ones((5, 5), np.uint8), iterations=1)},
    {'name': 'BitwiseNot', 'function': lambda frame: cv2.bitwise_not(frame)}
]
 
def apply_filter(frame, filter_index):
    """ Aplica o filtro especificado ao frame """
    filter_func = filters[filter_index]['function']
    return filter_func(frame)

def apply_magenta(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    magenta = np.zeros_like(frame)
    magenta[:, :, 0] = gray * 0.5  # Canal Azul - Menor intensidade
    magenta[:, :, 1] = gray * 0    # Canal Verde - Zero intensidade
    magenta[:, :, 2] = gray        # Canal Vermelho - Maior intensidade
    return magenta
 
def main():
    cap = cv2.VideoCapture(0)  
 
    if not cap.isOpened():
        print("Erro ao abrir a câmera.")
        return
 
    current_filter_index = 0
 
    while True:
        ret, frame = cap.read()
 
        if not ret:
            print("Erro ao capturar o frame.")
            break
 
        filtered_frame = apply_filter(frame, current_filter_index)
 
        cv2.imshow('Filtered Frame', filtered_frame)
 
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            break
        current_filter_index = (current_filter_index + 1) % len(filters)
 
    cap.release()
    cv2.destroyAllWindows()
 
if __name__ == "__main__":
    main()