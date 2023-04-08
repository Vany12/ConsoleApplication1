#include <opencv2/opencv.hpp>
#include <istream>


int main()
{
    cv::CascadeClassifier face_cascade;
    face_cascade.load("haarcascade_frontalface_alt.xml"); // загрузка классификатора для распознавания лиц

    cv::VideoCapture cap(0); // открытие веб-камеры
    if (!cap.isOpened()) // проверка, открыта ли камера
    {
        std::cout << "Ошибка при открытии камеры" << std::endl;
        return -1;
    }

    cv::Mat frame, gray_frame;
    std::vector<cv::Rect> faces;

    while (true) // бесконечный цикл обработки кадров
    {
        cap >> frame; // захват кадра с камеры
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY); // конвертирование кадра в оттенки серого
        face_cascade.detectMultiScale(gray_frame, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30)); // распознавание лиц на кадре

        for (int i = 0; i < faces.size(); i++) // отрисовка прямоугольников вокруг распознанных лиц
        {
            cv::rectangle(frame, faces[i], cv::Scalar(0, 0, 255), 2);
        }

        cv::imshow("Face detection", frame); // вывод кадра с отрисованными прямоугольниками

        if (cv::waitKey(1) == 27) // выход из цикла по нажатию клавиши Esc
        {
            break;
        }
    }

    cap.release(); // освобождение ресурсов камеры
    cv::destroyAllWindows(); // закрытие всех окон OpenCV

    return 0;
}