/************************************************************************************/
/*                                                                                  */
/*   A1 part3 tester file                                                           */
/*                                                                                  */
/*   To compile: g++ a1q3.cpp a1q3tester.cpp maze.cpp timer.cpp -std=c++0x          */
/*                                                                                  */
/*                                                                                  */
/*   You will also need the files maze1.txt, maze2.txt, maze3.txt                   */
/*                                                                                  */
/*                                                                                  */
/************************************************************************************/
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "wall.h"
#include "maze.h"
#include "timer.h"
int runMaze(Maze& theMaze, int path[], int startCell, int endCell);
bool test1(std::string& error);
bool test2(std::string& error);
bool test3(std::string& error);
bool test4(std::string& error);
bool test5(std::string& error);
bool test6(std::string& error);
bool test7(std::string& error);
bool test8(std::string& error);
bool test9(std::string& error);
bool test10(std::string& error);
const int numTests = 10;
typedef bool (*TestPtr)(std::string&);
bool checkPath(int path[], int pathLength, int correctPath[], int correctLength);
void printPath(const std::string& fname, int path[], int pathLength, int rows, int cols);

int main(void) {
    TestPtr runTest[numTests] = { test1, test2, test3, test4, test5,
        test6, test7, test8, test9, test10 };
    std::string msg;
    bool result = true;
    int numPassed = 0;
    Timer t;
    for (int i = 0; result && i < numTests; i++) {
        t.start();
        result = runTest[i](msg);
        t.stop();
        if (!result) {
            std::cout << msg << std::endl;
        }
        else {
            numPassed++;
            std::cout << "Test " << i + 1 << " passed!" << std::endl;
        }
    }
    if (numPassed == numTests) {
        std::cout << std::endl;
        std::cout << "Congratulations! You have passed testing for A1 part 3" << std::endl;
        std::cout << "Total Time: " << t.currtime() << std::endl << std::endl;
        std::cout << "The paths generated by your function have been written to your folder" << std::endl;
        std::cout << "The files are named test<number>path.txt" << std::endl << std::endl;
        std::cout << "To see what they look like: " << std::endl;
        std::cout << "   * go to: https://seneca-dsa555w20.github.io/dsa555-w20/a1q3.html" << std::endl;
        std::cout << "   * click the radio button to load the maze for the test" << std::endl;
        std::cout << "   * click the browse button to load the path file for that test" << std::endl;
    }
    else {
        std::cout << "Looks like you still have some work left to do" << std::endl;
    }

}
bool test1(std::string& error) {
    Maze theMaze("maze1.txt");
    int path[10];
    int pathLength = runMaze(theMaze, path, 0, 17);
    int correctLength = 10;
    int correct[10] = { 0, 1, 7, 8, 2, 3, 4, 5, 11, 17 };
    bool rc = true;
    if (!checkPath(path, pathLength, correct, correctLength)) {
        rc = false;
        if (pathLength != correctLength) {
            error = "Error 1a";
            error += ": runMaze() returned ";
            error += std::to_string(pathLength);
            error += ".  It should have returned ";
            error += std::to_string(correctLength);
        }
        else {
            error = "Error 1b: runMaze() does not create the correct path\n";
            error += "To see what is happening load the corresponding\n";
            error += "test and test1path.txt file at: \n";
            error += "https://seneca-dsa555w20.github.io/dsa555-w20/a1q3.html\n";
        }
    }
    printPath("test1path.txt", path, pathLength, 3, 6);
    return rc;

}
bool test2(std::string& error) {
    Maze theMaze("maze1.txt");
    int path[10];
    int pathLength = runMaze(theMaze, path, 8, 8);
    int correctLength = 1;
    int correct[1] = { 8 };
    bool rc = true;
    if (!checkPath(path, pathLength, correct, correctLength)) {
        rc = false;
        if (pathLength != correctLength) {
            error = "Error 2a";
            error += ": runMaze() returned ";
            error += std::to_string(pathLength);
            error += ".  It should have returned ";
            error += std::to_string(correctLength);
        }
        else {
            error = "Error 2b: runMaze() does not create the correct path\n";
            error += "To see what is happening load the corresponding\n";
            error += "test and test2path.txt file at: \n";
            error += "https://seneca-dsa555w20.github.io/dsa555-w20/a1q3.html\n";
        }
    }
    printPath("test2path.txt", path, pathLength, 3, 6);

    return rc;

}
bool test3(std::string& error) {
    Maze theMaze("maze1.txt");
    int path[8];
    int pathLength = runMaze(theMaze, path, 0, 5);
    int correctLength = 8;
    int correct[8] = { 0, 1, 7, 8, 2, 3, 4, 5 };
    bool rc = true;
    if (!checkPath(path, pathLength, correct, correctLength)) {
        rc = false;
        if (pathLength != correctLength) {
            error = "Error 3a";
            error += ": runMaze() returned ";
            error += std::to_string(pathLength);
            error += ".  It should have returned ";
            error += std::to_string(correctLength);
        }
        else {
            error = "Error 3b: runMaze() does not create the correct path\n";
            error += "To see what is happening load the corresponding\n";
            error += "test and test3path.txt file at: \n";
            error += "https://seneca-dsa555w20.github.io/dsa555-w20/a1q3.html\n";
        }
    }
    printPath("test3path.txt", path, pathLength, 3, 6);

    return rc;

}
bool test4(std::string& error) {
    Maze theMaze("maze2.txt");
    int path[200];
    int pathLength = runMaze(theMaze, path, 158, 41);
    int correctLength = 39;
    int correct[39] = { 158,157,177,197,196,195,175,174,173,172,
        171,151,131,111,112,92,72,52,53,33,
        13,12,11,10,9,29,28,27,47,67,
        66,86,85,84,83,63,62,42,41 };
    bool rc = true;
    if (!checkPath(path, pathLength, correct, correctLength)) {
        rc = false;
        if (pathLength != correctLength) {
            error = "Error 4a";
            error += ": runMaze() returned ";
            error += std::to_string(pathLength);
            error += ".  It should have returned ";
            error += std::to_string(correctLength);
        }
        else {
            error = "Error 4b: runMaze() does not create the correct path\n";
            error += "To see what is happening load the corresponding\n";
            error += "test and test4path.txt file at: \n";
            error += "https://seneca-dsa555w20.github.io/dsa555-w20/a1q3.html\n";

        }

    }
    printPath("test4path.txt", path, pathLength, 10, 20);

    return rc;
}
bool test5(std::string& error) {
    Maze theMaze("maze2.txt");
    int path[200];
    int pathLength = runMaze(theMaze, path, 199, 0);
    int correctLength = 45;
    int correct[45] = { 199,179,178,177,197,196,195,175,174,173,
        172,171,151,131,111,112,92,72,52,53,
        33,13,12,11,10,9,29,28,27,47,
        67,66,86,85,84,83,63,62,42,41,
        61,60,40,20,0 };
    bool rc = true;
    if (!checkPath(path, pathLength, correct, correctLength)) {
        rc = false;
        if (pathLength != correctLength) {
            error = "Error 5a";
            error += ": runMaze() returned ";
            error += std::to_string(pathLength);
            error += ".  It should have returned ";
            error += std::to_string(correctLength);
        }
        else {
            error = "Error 5b: runMaze() does not create the correct path\n";
            error += "To see what is happening load the corresponding\n";
            error += "test and test5path.txt file at: \n";
            error += "https://seneca-dsa555w20.github.io/dsa555-w20/a1q3.html\n";

        }
    }
    printPath("test5path.txt", path, pathLength, 10, 20);
    return rc;


}
bool test6(std::string& error) {
    Maze theMaze("maze3.txt");
    int path[1800];
    int pathLength = runMaze(theMaze, path, 1740, 59);
    int correctLength = 213;
    int correct[213] = { 1740,1680,1681,1682,1622,1562,1563,1503,1504,1444,
        1443,1383,1382,1381,1321,1322,1323,1324,1264,1204,
        1205,1145,1085,1084,1083,1023,1022,1082,1081,1021,
        961,901,841,842,782,722,723,724,664,604,
        605,606,666,667,607,547,487,488,489,429,
        430,370,371,372,312,313,253,254,255,195,
        196,197,198,199,259,319,318,317,377,378,
        379,439,499,498,497,496,556,616,676,736,
        796,795,855,915,975,1035,1095,1094,1154,1155,
        1156,1216,1276,1336,1337,1397,1398,1458,1459,1460,
        1520,1580,1581,1521,1522,1582,1583,1584,1585,1586,
        1526,1527,1528,1468,1467,1407,1408,1409,1410,1411,
        1351,1352,1412,1413,1414,1354,1294,1293,1292,1291,
        1231,1232,1172,1173,1174,1114,1115,1055,1056,996,
        997,998,999,939,879,878,877,817,816,815,
        814,754,694,634,633,632,572,512,513,514,
        515,516,576,636,696,756,757,697,698,638,
        639,579,519,520,521,522,523,583,584,585,
        645,646,647,648,649,650,651,591,590,530,
        529,469,409,349,350,290,230,231,232,172,
        112,113,173,233,234,235,236,176,116,56,
        57,58,59 };

    bool rc = true;
    if (!checkPath(path, pathLength, correct, correctLength)) {
        rc = false;
        if (pathLength != correctLength) {
            error = "Error 6a";
            error += ": runMaze() returned ";
            error += std::to_string(pathLength);
            error += ".  It should have returned ";
            error += std::to_string(correctLength);
        }
        else {
            error = "Error 6b: runMaze() does not create the correct path\n";
            error += "To see what is happening load the corresponding\n";
            error += "test and test6path.txt file at: \n";
            error += "https://seneca-dsa555w20.github.io/dsa555-w20/a1q3.html\n";
        }
    }

    printPath("test6path.txt", path, pathLength, 30, 60);
    return rc;

}
bool test7(std::string& error) {
    Maze theMaze("maze3.txt");
    int path[2000];
    int pathLength = runMaze(theMaze, path, 0, 959);
    int correctLength = 0;
    int correct[207] = {};
    bool rc = true;
    if (!checkPath(path, pathLength, correct, correctLength)) {
        rc = false;
        if (pathLength != correctLength) {
            error = "Error 7a";
            error += ": runMaze() returned ";
            error += std::to_string(pathLength);
            error += ".  It should have returned ";
            error += std::to_string(correctLength);
        }
        else {
            error = "Error 7b: runMaze() does not create the correct path\n";
            error += "To see what is happening load the corresponding\n";
            error += "test and test7path.txt file at: \n";
            error += "https://seneca-dsa555w20.github.io/dsa555-w20/a1q3.html\n";
        }
    }
    printPath("test7path.txt", path, pathLength, 30, 60);
    return rc;

}
bool test8(std::string& error) {
    Maze theMaze("maze3.txt");
    int path[2000];
    int correctLength = 174;
    int pathLength = runMaze(theMaze, path, 423, 1019);
    int correct[174] = { 423,424,484,483,543,603,604,605,606,666,
        667,607,547,487,488,489,429,430,370,371,
        372,312,313,253,254,255,195,196,197,198,
        199,259,319,318,317,377,378,379,439,499,
        498,497,496,556,616,676,736,796,795,855,
        915,975,1035,1095,1094,1154,1155,1156,1216,1276,
        1336,1337,1397,1398,1458,1459,1460,1520,1580,1581,
        1521,1522,1582,1583,1584,1585,1586,1526,1527,1528,
        1468,1467,1407,1408,1409,1410,1411,1351,1352,1412,
        1413,1414,1354,1294,1293,1292,1291,1231,1232,1172,
        1173,1174,1114,1115,1055,1056,996,997,998,999,
        939,879,878,877,817,816,815,814,754,694,
        634,633,632,572,512,513,514,515,516,576,
        636,696,756,757,697,698,638,639,579,519,
        520,521,522,523,583,584,585,645,646,647,
        648,708,768,828,829,889,949,950,1010,1011,
        951,952,953,893,894,895,955,1015,1075,1076,
        1077,1078,1018,1019 };
    bool rc = true;
    if (!checkPath(path, pathLength, correct, correctLength)) {
        rc = false;
        if (pathLength != correctLength) {
            error = "Error 8a";
            error += ": runMaze() returned ";
            error += std::to_string(pathLength);
            error += ".  It should have returned ";
            error += std::to_string(correctLength);
        }
        else {
            error = "Error 8b: runMaze() does not create the correct path\n";
            error += "To see what is happening load the corresponding\n";
            error += "test and test8path.txt file at: \n";
            error += "https://seneca-dsa555w20.github.io/dsa555-w20/a1q3.html\n";
        }

    }
    printPath("test8path.txt", path, pathLength, 30, 60);

    return rc;

}
bool test9(std::string& error) {
    Maze theMaze("maze3.txt");
    int path[2000];
    int pathLength = runMaze(theMaze, path, 959, 1019);
    int correctLength = 0;
    int correct[207] = {};

    bool rc = true;
    if (!checkPath(path, pathLength, correct, correctLength)) {
        rc = false;
        if (pathLength != correctLength) {
            error = "Error 9a";
            error += ": runMaze() returned ";
            error += std::to_string(pathLength);
            error += ".  It should have returned ";
            error += std::to_string(correctLength);
        }
        else {
            error = "Error 9b: runMaze() does not create the correct path\n";
            error += "To see what is happening load the corresponding\n";
            error += "test and test9path.txt file at: \n";
            error += "https://seneca-dsa555w20.github.io/dsa555-w20/a1q3.html\n";
        }
    }
    printPath("test9path.txt", path, pathLength, 30, 60);
    return rc;

}

bool test10(std::string& error) {
    Maze theMaze("maze3.txt");
    int path[2000];
    int correctLength = 7;
    int pathLength = runMaze(theMaze, path, 959, 839);
    int correct[7] = { 959, 899, 898, 838, 778, 779, 839 };
    bool rc = true;
    if (!checkPath(path, pathLength, correct, correctLength)) {
        rc = false;
        if (pathLength != correctLength) {
            error = "Error 10a";
            error += ": runMaze() returned ";
            error += std::to_string(pathLength);
            error += ".  It should have returned ";
            error += std::to_string(correctLength);
        }
        else {
            error = "Error 10b: runMaze() does not create the correct path\n";
            error += "To see what is happening load the corresponding\n";
            error += "test and test10path.txt file at: \n";
            error += "https://seneca-dsa555w20.github.io/dsa555-w20/a1q3.html\n";

        }
    }
    printPath("test10path.txt", path, pathLength, 30, 60);
    return rc;

}
bool checkPath(int path[], int pathLength, int correctPath[], int correctLength) {
    bool rc = true;
    if (pathLength != correctLength) {
        rc = false;
    }
    else {
        for (int i = 0; rc && i < pathLength; i++) {
            if (path[i] != correctPath[i]) {
                rc = false;
            }
        }
    }
    return rc;
}
void printPath(const std::string& fname, int path[], int pathLength, int rows, int cols) {
    std::ofstream fs(fname);
    fs << "{ \"rows\": " << rows << ", ";
    fs << "\"cols\": " << cols << ", ";

    fs << "\"pathLength\": " << pathLength << ", ";
    fs << "\"path\": [";
    for (int i = 0; i < pathLength - 1; i++) {
        fs << path[i] << ", ";
    }
    if (pathLength > 0) {
        fs << path[pathLength - 1];
    }
    fs << "]}" << std::endl;
    fs.close();
}