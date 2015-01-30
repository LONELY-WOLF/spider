/*
 * walk_legacy.c
 *
 *  Created on: Nov 13, 2014
 *      Author: wolf
 */


#include <stdint.h>
#include "legs.h"
#include "walk_legacy.h"

int Watch_Dog = 0;

uint8_t Route  = 0;

uint8_t Now_Route = 0;

int StepSize = 0, StepIndex = 0;

void (*WalkManager)();

struct SLeg
{
	uint16_t *H1;
	uint16_t *V2;
	uint16_t *V3;
} Leg[6];

void Init_Work();
void Step_Begin();
void Step_Walk();
void Step_End();
//void Step_Void();
//void End_Work();

#define ItemsOf(X) sizeof(X) / sizeof(X[0])


uint16_t Walk1_Begin_L1[] = {1500, 1448, 1399, 1356, 1320, 1295, 1278};
uint16_t Walk1_L1[] = {1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1278, 1284, 1302, 1331, 1369, 1415, 1465, 1517, 1569, 1616, 1657, 1689, 1711, 1722, 1719, 1705, 1680, 1644, 1601, 1552, 1500, 1448, 1399, 1356, 1320, 1295, 1281, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003};
uint16_t Walk1_End_L1[] = {1278, 1284, 1302, 1331, 1369, 1415, 1500};

uint16_t Walk1_Begin_L2[] = {1500, 1448, 1399, 1356, 1320, 1295, 1278};
uint16_t Walk1_L2[] = {1278, 1284, 1302, 1331, 1369, 1415, 1465, 1517, 1569, 1616, 1657, 1689, 1711, 1722, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1722, 1716, 1698, 1669, 1631, 1585, 1535, 1483, 1431, 1384, 1343, 1311, 1289, 1278};
uint16_t Walk1_End_L2[] = {1278, 1284, 1302, 1331, 1369, 1415, 1500};

uint16_t Walk1_Begin_L3[] = {1500, 1552, 1601, 1644, 1680, 1705, 1722};
uint16_t Walk1_L3[] = {1722, 1716, 1698, 1669, 1631, 1585, 1535, 1483, 1431, 1384, 1343, 1311, 1289, 1278, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1278, 1284, 1302, 1331, 1369, 1415, 1465, 1517, 1569, 1616, 1657, 1689, 1711, 1722};
uint16_t Walk1_End_L3[] = {1722, 1716, 1698, 1669, 1631, 1585, 1500};

uint16_t Walk1_Begin_L4[] = {1500, 1552, 1601, 1644, 1680, 1705, 1722};
uint16_t Walk1_L4[] = {1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1722, 1716, 1698, 1669, 1631, 1585, 1535, 1483, 1431, 1384, 1343, 1311, 1289, 1278, 1281, 1295, 1320, 1356, 1399, 1448, 1500, 1552, 1601, 1644, 1680, 1705, 1719, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003};
uint16_t Walk1_End_L4[] = {1722, 1716, 1698, 1669, 1631, 1585, 1500};

uint16_t Walk1_Begin_L5[] = {1500, 1448, 1399, 1356, 1320, 1295, 1278};
uint16_t Walk1_L5[] = {1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1278, 1284, 1302, 1331, 1369, 1415, 1465, 1517, 1569, 1616, 1657, 1689, 1711, 1722, 1719, 1705, 1680, 1644, 1601, 1552, 1500, 1448, 1399, 1356, 1320, 1295, 1281, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003, 1.277778e+003};
uint16_t Walk1_End_L5[] = {1278, 1284, 1302, 1331, 1369, 1415, 1500};

uint16_t Walk1_Begin_L6[] = {1500, 1448, 1399, 1356, 1320, 1295, 1278};
uint16_t Walk1_L6[] = {1278, 1284, 1302, 1331, 1369, 1415, 1465, 1517, 1569, 1616, 1657, 1689, 1711, 1722, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1.722222e+003, 1722, 1716, 1698, 1669, 1631, 1585, 1535, 1483, 1431, 1384, 1343, 1311, 1289, 1278};
uint16_t Walk1_End_L6[] = {1278, 1284, 1302, 1331, 1369, 1415, 1500};


uint16_t Walk_forward_Begin_L1[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Walk_forward_L1[] = {1500, 1478, 1457, 1435, 1414, 1394, 1374, 1355, 1337, 1320, 1304, 1289, 1275, 1263, 1252, 1243, 1236, 1230, 1226, 1223, 1222, 1222, 1224, 1230, 1239, 1252, 1269, 1289, 1311, 1337, 1364, 1394, 1425, 1457, 1489, 1522, 1554, 1586, 1616, 1645, 1672, 1696, 1718, 1737, 1752, 1764, 1772, 1777, 1778, 1777, 1774, 1770, 1764, 1757, 1748, 1737, 1725, 1711, 1696, 1680, 1663, 1645, 1626, 1606, 1586, 1565, 1543, 1522, 1500};
uint16_t Walk_forward_End_L1[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t Walk_forward_Begin_L2[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Walk_forward_L2[] = {1500, 1467, 1435, 1404, 1374, 1346, 1320, 1296, 1275, 1258, 1243, 1233, 1226, 1222, 1222, 1223, 1226, 1230, 1236, 1243, 1252, 1263, 1275, 1289, 1304, 1320, 1337, 1355, 1374, 1394, 1414, 1435, 1457, 1478, 1500, 1522, 1543, 1565, 1586, 1606, 1626, 1645, 1663, 1680, 1696, 1711, 1725, 1737, 1748, 1757, 1764, 1770, 1774, 1777, 1778, 1778, 1776, 1770, 1761, 1748, 1731, 1711, 1689, 1663, 1636, 1606, 1575, 1543, 1500};
uint16_t Walk_forward_End_L2[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t Walk_forward_Begin_L3[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Walk_forward_L3[] = {1500, 1533, 1565, 1596, 1626, 1654, 1680, 1704, 1725, 1742, 1757, 1767, 1774, 1778, 1778, 1777, 1774, 1770, 1764, 1757, 1748, 1737, 1725, 1711, 1696, 1680, 1663, 1645, 1626, 1606, 1586, 1565, 1543, 1522, 1500, 1478, 1457, 1435, 1414, 1394, 1374, 1355, 1337, 1320, 1304, 1289, 1275, 1263, 1252, 1243, 1236, 1230, 1226, 1223, 1222, 1222, 1224, 1230, 1239, 1252, 1269, 1289, 1311, 1337, 1364, 1394, 1425, 1457, 1500};
uint16_t Walk_forward_End_L3[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t Walk_forward_Begin_L4[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Walk_forward_L4[] = {1500, 1522, 1543, 1565, 1586, 1606, 1626, 1645, 1663, 1680, 1696, 1711, 1725, 1737, 1748, 1757, 1764, 1770, 1774, 1777, 1778, 1778, 1776, 1770, 1761, 1748, 1731, 1711, 1689, 1663, 1636, 1606, 1575, 1543, 1511, 1478, 1446, 1414, 1384, 1355, 1328, 1304, 1282, 1263, 1248, 1236, 1228, 1223, 1222, 1223, 1226, 1230, 1236, 1243, 1252, 1263, 1275, 1289, 1304, 1320, 1337, 1355, 1374, 1394, 1414, 1435, 1457, 1478, 1500};
uint16_t Walk_forward_End_L4[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t Walk_forward_Begin_L5[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Walk_forward_L5[] = {1500, 1478, 1457, 1435, 1414, 1394, 1374, 1355, 1337, 1320, 1304, 1289, 1275, 1263, 1252, 1243, 1236, 1230, 1226, 1223, 1222, 1222, 1224, 1230, 1239, 1252, 1269, 1289, 1311, 1337, 1364, 1394, 1425, 1457, 1489, 1522, 1554, 1586, 1616, 1645, 1672, 1696, 1718, 1737, 1752, 1764, 1772, 1777, 1778, 1777, 1774, 1770, 1764, 1757, 1748, 1737, 1725, 1711, 1696, 1680, 1663, 1645, 1626, 1606, 1586, 1565, 1543, 1522, 1500};
uint16_t Walk_forward_End_L5[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t Walk_forward_Begin_L6[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Walk_forward_L6[] = {1500, 1467, 1435, 1404, 1374, 1346, 1320, 1296, 1275, 1258, 1243, 1233, 1226, 1222, 1222, 1223, 1226, 1230, 1236, 1243, 1252, 1263, 1275, 1289, 1304, 1320, 1337, 1355, 1374, 1394, 1414, 1435, 1457, 1478, 1500, 1522, 1543, 1565, 1586, 1606, 1626, 1645, 1663, 1680, 1696, 1711, 1725, 1737, 1748, 1757, 1764, 1770, 1774, 1777, 1778, 1778, 1776, 1770, 1761, 1748, 1731, 1711, 1689, 1663, 1636, 1606, 1575, 1543, 1500};
uint16_t Walk_forward_End_L6[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};


uint16_t Walk_back_Begin_L1[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Walk_back_L1[] = {1500, 1522, 1543, 1565, 1586, 1606, 1626, 1645, 1663, 1680, 1696, 1711, 1725, 1737, 1748, 1757, 1764, 1770, 1774, 1777, 1778, 1778, 1776, 1770, 1761, 1748, 1731, 1711, 1689, 1663, 1636, 1606, 1575, 1543, 1511, 1478, 1446, 1414, 1384, 1355, 1328, 1304, 1282, 1263, 1248, 1236, 1228, 1223, 1222, 1223, 1226, 1230, 1236, 1243, 1252, 1263, 1275, 1289, 1304, 1320, 1337, 1355, 1374, 1394, 1414, 1435, 1457, 1478, 1500};
uint16_t Walk_back_End_L1[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t Walk_back_Begin_L2[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Walk_back_L2[] = {1500, 1533, 1565, 1596, 1626, 1654, 1680, 1704, 1725, 1742, 1757, 1767, 1774, 1778, 1778, 1777, 1774, 1770, 1764, 1757, 1748, 1737, 1725, 1711, 1696, 1680, 1663, 1645, 1626, 1606, 1586, 1565, 1543, 1522, 1500, 1478, 1457, 1435, 1414, 1394, 1374, 1355, 1337, 1320, 1304, 1289, 1275, 1263, 1252, 1243, 1236, 1230, 1226, 1223, 1222, 1222, 1224, 1230, 1239, 1252, 1269, 1289, 1311, 1337, 1364, 1394, 1425, 1457, 1500};
uint16_t Walk_back_End_L2[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t Walk_back_Begin_L3[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Walk_back_L3[] = {1500, 1467, 1435, 1404, 1374, 1346, 1320, 1296, 1275, 1258, 1243, 1233, 1226, 1222, 1222, 1223, 1226, 1230, 1236, 1243, 1252, 1263, 1275, 1289, 1304, 1320, 1337, 1355, 1374, 1394, 1414, 1435, 1457, 1478, 1500, 1522, 1543, 1565, 1586, 1606, 1626, 1645, 1663, 1680, 1696, 1711, 1725, 1737, 1748, 1757, 1764, 1770, 1774, 1777, 1778, 1778, 1776, 1770, 1761, 1748, 1731, 1711, 1689, 1663, 1636, 1606, 1575, 1543, 1500};
uint16_t Walk_back_End_L3[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t Walk_back_Begin_L4[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Walk_back_L4[] = {1500, 1478, 1457, 1435, 1414, 1394, 1374, 1355, 1337, 1320, 1304, 1289, 1275, 1263, 1252, 1243, 1236, 1230, 1226, 1223, 1222, 1222, 1224, 1230, 1239, 1252, 1269, 1289, 1311, 1337, 1364, 1394, 1425, 1457, 1489, 1522, 1554, 1586, 1616, 1645, 1672, 1696, 1718, 1737, 1752, 1764, 1772, 1777, 1778, 1777, 1774, 1770, 1764, 1757, 1748, 1737, 1725, 1711, 1696, 1680, 1663, 1645, 1626, 1606, 1586, 1565, 1543, 1522, 1500};
uint16_t Walk_back_End_L4[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t Walk_back_Begin_L5[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Walk_back_L5[] = {1500, 1522, 1543, 1565, 1586, 1606, 1626, 1645, 1663, 1680, 1696, 1711, 1725, 1737, 1748, 1757, 1764, 1770, 1774, 1777, 1778, 1778, 1776, 1770, 1761, 1748, 1731, 1711, 1689, 1663, 1636, 1606, 1575, 1543, 1511, 1478, 1446, 1414, 1384, 1355, 1328, 1304, 1282, 1263, 1248, 1236, 1228, 1223, 1222, 1223, 1226, 1230, 1236, 1243, 1252, 1263, 1275, 1289, 1304, 1320, 1337, 1355, 1374, 1394, 1414, 1435, 1457, 1478, 1500};
uint16_t Walk_back_End_L5[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t Walk_back_Begin_L6[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Walk_back_L6[] = {1500, 1533, 1565, 1596, 1626, 1654, 1680, 1704, 1725, 1742, 1757, 1767, 1774, 1778, 1778, 1777, 1774, 1770, 1764, 1757, 1748, 1737, 1725, 1711, 1696, 1680, 1663, 1645, 1626, 1606, 1586, 1565, 1543, 1522, 1500, 1478, 1457, 1435, 1414, 1394, 1374, 1355, 1337, 1320, 1304, 1289, 1275, 1263, 1252, 1243, 1236, 1230, 1226, 1223, 1222, 1222, 1224, 1230, 1239, 1252, 1269, 1289, 1311, 1337, 1364, 1394, 1425, 1457, 1500};
uint16_t Walk_back_End_L6[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};


uint16_t turn_right_Begin_L1[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t turn_right_L1[] = {1500, 1478, 1457, 1435, 1414, 1394, 1374, 1355, 1337, 1320, 1304, 1289, 1275, 1263, 1252, 1243, 1236, 1230, 1226, 1223, 1222, 1222, 1224, 1230, 1239, 1252, 1269, 1289, 1311, 1337, 1364, 1394, 1425, 1457, 1489, 1522, 1554, 1586, 1616, 1645, 1672, 1696, 1718, 1737, 1752, 1764, 1772, 1777, 1778, 1777, 1774, 1770, 1764, 1757, 1748, 1737, 1725, 1711, 1696, 1680, 1663, 1645, 1626, 1606, 1586, 1565, 1543, 1522, 1500};
uint16_t turn_right_End_L1[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t turn_right_Begin_L2[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t turn_right_L2[] = {1500, 1533, 1565, 1596, 1626, 1654, 1680, 1704, 1725, 1742, 1757, 1767, 1774, 1778, 1778, 1777, 1774, 1770, 1764, 1757, 1748, 1737, 1725, 1711, 1696, 1680, 1663, 1645, 1626, 1606, 1586, 1565, 1543, 1522, 1500, 1478, 1457, 1435, 1414, 1394, 1374, 1355, 1337, 1320, 1304, 1289, 1275, 1263, 1252, 1243, 1236, 1230, 1226, 1223, 1222, 1222, 1224, 1230, 1239, 1252, 1269, 1289, 1311, 1337, 1364, 1394, 1425, 1457, 1500};
uint16_t turn_right_End_L2[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t turn_right_Begin_L3[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t turn_right_L3[] = {1500, 1533, 1565, 1596, 1626, 1654, 1680, 1704, 1725, 1742, 1757, 1767, 1774, 1778, 1778, 1777, 1774, 1770, 1764, 1757, 1748, 1737, 1725, 1711, 1696, 1680, 1663, 1645, 1626, 1606, 1586, 1565, 1543, 1522, 1500, 1478, 1457, 1435, 1414, 1394, 1374, 1355, 1337, 1320, 1304, 1289, 1275, 1263, 1252, 1243, 1236, 1230, 1226, 1223, 1222, 1222, 1224, 1230, 1239, 1252, 1269, 1289, 1311, 1337, 1364, 1394, 1425, 1457, 1500};
uint16_t turn_right_End_L3[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t turn_right_Begin_L4[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t turn_right_L4[] = {1500, 1478, 1457, 1435, 1414, 1394, 1374, 1355, 1337, 1320, 1304, 1289, 1275, 1263, 1252, 1243, 1236, 1230, 1226, 1223, 1222, 1222, 1224, 1230, 1239, 1252, 1269, 1289, 1311, 1337, 1364, 1394, 1425, 1457, 1489, 1522, 1554, 1586, 1616, 1645, 1672, 1696, 1718, 1737, 1752, 1764, 1772, 1777, 1778, 1777, 1774, 1770, 1764, 1757, 1748, 1737, 1725, 1711, 1696, 1680, 1663, 1645, 1626, 1606, 1586, 1565, 1543, 1522, 1500};
uint16_t turn_right_End_L4[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t turn_right_Begin_L5[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t turn_right_L5[] = {1500, 1478, 1457, 1435, 1414, 1394, 1374, 1355, 1337, 1320, 1304, 1289, 1275, 1263, 1252, 1243, 1236, 1230, 1226, 1223, 1222, 1222, 1224, 1230, 1239, 1252, 1269, 1289, 1311, 1337, 1364, 1394, 1425, 1457, 1489, 1522, 1554, 1586, 1616, 1645, 1672, 1696, 1718, 1737, 1752, 1764, 1772, 1777, 1778, 1777, 1774, 1770, 1764, 1757, 1748, 1737, 1725, 1711, 1696, 1680, 1663, 1645, 1626, 1606, 1586, 1565, 1543, 1522, 1500};
uint16_t turn_right_End_L5[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t turn_right_Begin_L6[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t turn_right_L6[] = {1500, 1533, 1565, 1596, 1626, 1654, 1680, 1704, 1725, 1742, 1757, 1767, 1774, 1778, 1778, 1777, 1774, 1770, 1764, 1757, 1748, 1737, 1725, 1711, 1696, 1680, 1663, 1645, 1626, 1606, 1586, 1565, 1543, 1522, 1500, 1478, 1457, 1435, 1414, 1394, 1374, 1355, 1337, 1320, 1304, 1289, 1275, 1263, 1252, 1243, 1236, 1230, 1226, 1223, 1222, 1222, 1224, 1230, 1239, 1252, 1269, 1289, 1311, 1337, 1364, 1394, 1425, 1457, 1500};
uint16_t turn_right_End_L6[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};


uint16_t turn_left_Begin_L1[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t turn_left_L1[] = {1500, 1522, 1543, 1565, 1586, 1606, 1626, 1645, 1663, 1680, 1696, 1711, 1725, 1737, 1748, 1757, 1764, 1770, 1774, 1777, 1778, 1778, 1776, 1770, 1761, 1748, 1731, 1711, 1689, 1663, 1636, 1606, 1575, 1543, 1511, 1478, 1446, 1414, 1384, 1355, 1328, 1304, 1282, 1263, 1248, 1236, 1228, 1223, 1222, 1223, 1226, 1230, 1236, 1243, 1252, 1263, 1275, 1289, 1304, 1320, 1337, 1355, 1374, 1394, 1414, 1435, 1457, 1478, 1500};
uint16_t turn_left_End_L1[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t turn_left_Begin_L2[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t turn_left_L2[] = {1500, 1467, 1435, 1404, 1374, 1346, 1320, 1296, 1275, 1258, 1243, 1233, 1226, 1222, 1222, 1223, 1226, 1230, 1236, 1243, 1252, 1263, 1275, 1289, 1304, 1320, 1337, 1355, 1374, 1394, 1414, 1435, 1457, 1478, 1500, 1522, 1543, 1565, 1586, 1606, 1626, 1645, 1663, 1680, 1696, 1711, 1725, 1737, 1748, 1757, 1764, 1770, 1774, 1777, 1778, 1778, 1776, 1770, 1761, 1748, 1731, 1711, 1689, 1663, 1636, 1606, 1575, 1543, 1500};
uint16_t turn_left_End_L2[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t turn_left_Begin_L3[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t turn_left_L3[] = {1500, 1467, 1435, 1404, 1374, 1346, 1320, 1296, 1275, 1258, 1243, 1233, 1226, 1222, 1222, 1223, 1226, 1230, 1236, 1243, 1252, 1263, 1275, 1289, 1304, 1320, 1337, 1355, 1374, 1394, 1414, 1435, 1457, 1478, 1500, 1522, 1543, 1565, 1586, 1606, 1626, 1645, 1663, 1680, 1696, 1711, 1725, 1737, 1748, 1757, 1764, 1770, 1774, 1777, 1778, 1778, 1776, 1770, 1761, 1748, 1731, 1711, 1689, 1663, 1636, 1606, 1575, 1543, 1500};
uint16_t turn_left_End_L3[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t turn_left_Begin_L4[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t turn_left_L4[] = {1500, 1522, 1543, 1565, 1586, 1606, 1626, 1645, 1663, 1680, 1696, 1711, 1725, 1737, 1748, 1757, 1764, 1770, 1774, 1777, 1778, 1778, 1776, 1770, 1761, 1748, 1731, 1711, 1689, 1663, 1636, 1606, 1575, 1543, 1511, 1478, 1446, 1414, 1384, 1355, 1328, 1304, 1282, 1263, 1248, 1236, 1228, 1223, 1222, 1223, 1226, 1230, 1236, 1243, 1252, 1263, 1275, 1289, 1304, 1320, 1337, 1355, 1374, 1394, 1414, 1435, 1457, 1478, 1500};
uint16_t turn_left_End_L4[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t turn_left_Begin_L5[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t turn_left_L5[] = {1500, 1522, 1543, 1565, 1586, 1606, 1626, 1645, 1663, 1680, 1696, 1711, 1725, 1737, 1748, 1757, 1764, 1770, 1774, 1777, 1778, 1778, 1776, 1770, 1761, 1748, 1731, 1711, 1689, 1663, 1636, 1606, 1575, 1543, 1511, 1478, 1446, 1414, 1384, 1355, 1328, 1304, 1282, 1263, 1248, 1236, 1228, 1223, 1222, 1223, 1226, 1230, 1236, 1243, 1252, 1263, 1275, 1289, 1304, 1320, 1337, 1355, 1374, 1394, 1414, 1435, 1457, 1478, 1500};
uint16_t turn_left_End_L5[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};

uint16_t turn_left_Begin_L6[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t turn_left_L6[] = {1500, 1467, 1435, 1404, 1374, 1346, 1320, 1296, 1275, 1258, 1243, 1233, 1226, 1222, 1222, 1223, 1226, 1230, 1236, 1243, 1252, 1263, 1275, 1289, 1304, 1320, 1337, 1355, 1374, 1394, 1414, 1435, 1457, 1478, 1500, 1522, 1543, 1565, 1586, 1606, 1626, 1645, 1663, 1680, 1696, 1711, 1725, 1737, 1748, 1757, 1764, 1770, 1774, 1777, 1778, 1778, 1776, 1770, 1761, 1748, 1731, 1711, 1689, 1663, 1636, 1606, 1575, 1543, 1500};
uint16_t turn_left_End_L6[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};


uint16_t Stop_Begin[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Stop[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint16_t Stop_End[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500};


uint16_t Full_Stop_All_Legs[] = {1500};

uint16_t	Count = 0;

void SetRoute(uint8_t route)
{
	Now_Route = route;
	Watch_Dog = 0;
}

void Init_Work()
{
	for(int i = 0; i < 6; i++)
	{
		Leg[i].H1 = Full_Stop_All_Legs;
		Leg[i].V2 = Full_Stop_All_Legs;
		Leg[i].V3 = Full_Stop_All_Legs;
	}

	StepSize = ItemsOf(Full_Stop_All_Legs);

	//Count++;
	//if (Count >= 10)
	//{
		//Count = 0;
		WalkManager = Step_Begin;
	//}

	//Step_Begin();
}

void Step_Begin()
{
	Route = Now_Route;

	switch (Route)
	{
		case 1:
		{
			Leg[0].H1 = Walk_forward_Begin_L1;
			Leg[1].H1 = Walk_forward_Begin_L2;
			Leg[2].H1 = Walk_forward_Begin_L3;
			Leg[3].H1 = Walk_forward_Begin_L4;
			Leg[4].H1 = Walk_forward_Begin_L5;
			Leg[5].H1 = Walk_forward_Begin_L6;

			StepSize = ItemsOf(Walk_forward_Begin_L6);
			break;
		}
		case 2:
		{
			Leg[0].H1 = Walk_back_Begin_L1;
			Leg[1].H1 = Walk_back_Begin_L2;
			Leg[2].H1 = Walk_back_Begin_L3;
			Leg[3].H1 = Walk_back_Begin_L4;
			Leg[4].H1 = Walk_back_Begin_L5;
			Leg[5].H1 = Walk_back_Begin_L6;

			StepSize = ItemsOf(Walk_back_Begin_L6);
			break;
		}
		case 3:
		{
			Leg[0].H1 = turn_right_Begin_L1;
			Leg[1].H1 = turn_right_Begin_L2;
			Leg[2].H1 = turn_right_Begin_L3;
			Leg[3].H1 = turn_right_Begin_L4;
			Leg[4].H1 = turn_right_Begin_L5;
			Leg[5].H1 = turn_right_Begin_L6;

			StepSize = ItemsOf(turn_right_Begin_L6);
			break;
		}
		case 4:
		{
			Leg[0].H1 = turn_left_Begin_L1;
			Leg[1].H1 = turn_left_Begin_L2;
			Leg[2].H1 = turn_left_Begin_L3;
			Leg[3].H1 = turn_left_Begin_L4;
			Leg[4].H1 = turn_left_Begin_L5;
			Leg[5].H1 = turn_left_Begin_L6;

			StepSize = ItemsOf(turn_left_Begin_L6);
			break;
		}
		case 5:
		{
			/*Leg[0].H1 = DynTable;
			Leg[1].H1 = DynTable + 1;
			Leg[2].H1 = DynTable + 2;
			Leg[3].H1 = DynTable + 3;
			Leg[4].H1 = DynTable + 4;
			Leg[5].H1 = DynTable + 5;

			StepSize = 1;*/
			break;
		}
		default:
		{
			Leg[0].H1 = Stop_Begin;
			Leg[1].H1 = Stop_Begin;
			Leg[2].H1 = Stop_Begin;
			Leg[3].H1 = Stop_Begin;
			Leg[4].H1 = Stop_Begin;
			Leg[5].H1 = Stop_Begin;

			StepSize = ItemsOf(Stop_Begin);
			break;
		}
	}
	if(Route)
	{
		Leg[0].V2 = Walk1_Begin_L1;
		Leg[1].V2 = Walk1_Begin_L2;
		Leg[2].V2 = Walk1_Begin_L3;
		Leg[3].V2 = Walk1_Begin_L4;
		Leg[4].V2 = Walk1_Begin_L5;
		Leg[5].V2 = Walk1_Begin_L6;

		Leg[0].V3 = Walk1_Begin_L1;
		Leg[1].V3 = Walk1_Begin_L2;
		Leg[2].V3 = Walk1_Begin_L3;
		Leg[3].V3 = Walk1_Begin_L4;
		Leg[4].V3 = Walk1_Begin_L5;
		Leg[5].V3 = Walk1_Begin_L6;
	}
	else
	{
		Leg[0].V2 = Stop_Begin;
		Leg[1].V2 = Stop_Begin;
		Leg[2].V2 = Stop_Begin;
		Leg[3].V2 = Stop_Begin;
		Leg[4].V2 = Stop_Begin;
		Leg[5].V2 = Stop_Begin;

		Leg[0].V3 = Stop_Begin;
		Leg[1].V3 = Stop_Begin;
		Leg[2].V3 = Stop_Begin;
		Leg[3].V3 = Stop_Begin;
		Leg[4].V3 = Stop_Begin;
		Leg[5].V3 = Stop_Begin;
	}

	StepSize = ItemsOf(Walk1_Begin_L6);
	WalkManager = Step_Walk;
}

void Step_Walk()
{
	if((Watch_Dog++) > 5) //5 steps without update
	{
		Now_Route = 0;
	}
	if (Route != Now_Route)
	{
		WalkManager = Step_End;
		WalkManager();
		return;
	}

	if (Route == 0)
	{
		Init_Work();
		return;
	}

	switch(Route)
	{
		case 1:
		{
			Leg[0].H1 = Walk_forward_L1;
			Leg[1].H1 = Walk_forward_L2;
			Leg[2].H1 = Walk_forward_L3;
			Leg[3].H1 = Walk_forward_L4;
			Leg[4].H1 = Walk_forward_L5;
			Leg[5].H1 = Walk_forward_L6;

			StepSize = ItemsOf(Walk_forward_L6);
			break;
		}
		case 2:
		{
			Leg[0].H1 = Walk_back_L1;
			Leg[1].H1 = Walk_back_L2;
			Leg[2].H1 = Walk_back_L3;
			Leg[3].H1 = Walk_back_L4;
			Leg[4].H1 = Walk_back_L5;
			Leg[5].H1 = Walk_back_L6;

			StepSize = ItemsOf(Walk_back_L6);
			break;
		}
		case 3:
		{
			Leg[0].H1 = turn_right_L1;
			Leg[1].H1 = turn_right_L2;
			Leg[2].H1 = turn_right_L3;
			Leg[3].H1 = turn_right_L4;
			Leg[4].H1 = turn_right_L5;
			Leg[5].H1 = turn_right_L6;

			StepSize = ItemsOf(turn_right_L6);
			break;
		}
		case 4:
		{
			Leg[0].H1 = turn_left_L1;
			Leg[1].H1 = turn_left_L2;
			Leg[2].H1 = turn_left_L3;
			Leg[3].H1 = turn_left_L4;
			Leg[4].H1 = turn_left_L5;
			Leg[5].H1 = turn_left_L6;

			StepSize = ItemsOf(turn_left_L6);
			break;
		}
		case 5:
		{
			/*
			Leg[0].H1 = DynTable;
			Leg[1].H1 = DynTable + 1;
			Leg[2].H1 = DynTable + 2;
			Leg[3].H1 = DynTable + 3;
			Leg[4].H1 = DynTable + 4;
			Leg[5].H1 = DynTable + 5;
			*/
			StepSize = 1;
			break;
		}
		default:
		{
			Leg[0].H1 = Stop;
			Leg[1].H1 = Stop;
			Leg[2].H1 = Stop;
			Leg[3].H1 = Stop;
			Leg[4].H1 = Stop;
			Leg[5].H1 = Stop;

			StepSize = ItemsOf(Stop);
			break;
		}
	}
	if(Route)
	{
		Leg[0].V2 = Walk1_L1;
		Leg[1].V2 = Walk1_L2;
		Leg[2].V2 = Walk1_L3;
		Leg[3].V2 = Walk1_L4;
		Leg[4].V2 = Walk1_L5;
		Leg[5].V2 = Walk1_L6;

		Leg[0].V3 = Walk1_L1;
		Leg[1].V3 = Walk1_L2;
		Leg[2].V3 = Walk1_L3;
		Leg[3].V3 = Walk1_L4;
		Leg[4].V3 = Walk1_L5;
		Leg[5].V3 = Walk1_L6;
	}
	else
	{
		Leg[0].V2 = Stop;
		Leg[1].V2 = Stop;
		Leg[2].V2 = Stop;
		Leg[3].V2 = Stop;
		Leg[4].V2 = Stop;
		Leg[5].V2 = Stop;

		Leg[0].V3 = Stop;
		Leg[1].V3 = Stop;
		Leg[2].V3 = Stop;
		Leg[3].V3 = Stop;
		Leg[4].V3 = Stop;
		Leg[5].V3 = Stop;
	}

	StepSize = ItemsOf(Walk1_L6);
}

void Step_End()
{
	switch(Route)
	{
		case 1:
		{
			Leg[0].H1 = Walk_forward_End_L1;
			Leg[1].H1 = Walk_forward_End_L2;
			Leg[2].H1 = Walk_forward_End_L3;
			Leg[3].H1 = Walk_forward_End_L4;
			Leg[4].H1 = Walk_forward_End_L5;
			Leg[5].H1 = Walk_forward_End_L6;

			StepSize = ItemsOf(Walk_forward_End_L6);
			break;
		}
		case 2:
		{
			Leg[0].H1 = Walk_back_End_L1;
			Leg[1].H1 = Walk_back_End_L2;
			Leg[2].H1 = Walk_back_End_L3;
			Leg[3].H1 = Walk_back_End_L4;
			Leg[4].H1 = Walk_back_End_L5;
			Leg[5].H1 = Walk_back_End_L6;

			StepSize = ItemsOf(Walk_back_End_L6);
			break;
		}
		case 3:
		{
			Leg[0].H1 = turn_right_End_L1;
			Leg[1].H1 = turn_right_End_L2;
			Leg[2].H1 = turn_right_End_L3;
			Leg[3].H1 = turn_right_End_L4;
			Leg[4].H1 = turn_right_End_L5;
			Leg[5].H1 = turn_right_End_L6;

			StepSize = ItemsOf(turn_right_End_L6);
			break;
		}
		case 4:
		{
			Leg[0].H1 = turn_left_End_L1;
			Leg[1].H1 = turn_left_End_L2;
			Leg[2].H1 = turn_left_End_L3;
			Leg[3].H1 = turn_left_End_L4;
			Leg[4].H1 = turn_left_End_L5;
			Leg[5].H1 = turn_left_End_L6;

			StepSize = ItemsOf(turn_left_End_L6);
			break;
		}
		case 5:
		{
		/*
			Leg[0].H1 = Full_Stop_All_Legs;
			Leg[1].H1 = Full_Stop_All_Legs;
			Leg[2].H1 = Full_Stop_All_Legs;
			Leg[3].H1 = Full_Stop_All_Legs;
			Leg[4].H1 = Full_Stop_All_Legs;
			Leg[5].H1 = Full_Stop_All_Legs;

			StepSize = ItemsOf(Full_Stop_All_Legs);
			*/
			StepSize = 1;
			break;
		}
		default:
		{
			Route = 0;

			Leg[0].H1 = Stop_End;
			Leg[1].H1 = Stop_End;
			Leg[2].H1 = Stop_End;
			Leg[3].H1 = Stop_End;
			Leg[4].H1 = Stop_End;
			Leg[5].H1 = Stop_End;

			StepSize = ItemsOf(Stop_End);
			break;
		}
	}
	if(Route)
	{
		Leg[0].V2 = Walk1_End_L1;
		Leg[1].V2 = Walk1_End_L2;
		Leg[2].V2 = Walk1_End_L3;
		Leg[3].V2 = Walk1_End_L4;
		Leg[4].V2 = Walk1_End_L5;
		Leg[5].V2 = Walk1_End_L6;

		Leg[0].V3 = Walk1_End_L1;
		Leg[1].V3 = Walk1_End_L2;
		Leg[2].V3 = Walk1_End_L3;
		Leg[3].V3 = Walk1_End_L4;
		Leg[4].V3 = Walk1_End_L5;
		Leg[5].V3 = Walk1_End_L6;
	}
	else
	{
		Leg[0].V2 = Stop_End;
		Leg[1].V2 = Stop_End;
		Leg[2].V2 = Stop_End;
		Leg[3].V2 = Stop_End;
		Leg[4].V2 = Stop_End;
		Leg[5].V2 = Stop_End;

		Leg[0].V3 = Stop_End;
		Leg[1].V3 = Stop_End;
		Leg[2].V3 = Stop_End;
		Leg[3].V3 = Stop_End;
		Leg[4].V3 = Stop_End;
		Leg[5].V3 = Stop_End;
	}

	StepSize = ItemsOf(Walk1_End_L6);

	WalkManager = Init_Work;
}

/*
void End_Work()
{
	Set(Legs + 0, Full_Stop_All_Legs, Full_Stop_All_Legs, Full_Stop_All_Legs);
	Set(Legs + 1, Full_Stop_All_Legs, Full_Stop_All_Legs, Full_Stop_All_Legs);
	Set(Legs + 2, Full_Stop_All_Legs, Full_Stop_All_Legs, Full_Stop_All_Legs);
	Set(Legs + 3, Full_Stop_All_Legs, Full_Stop_All_Legs, Full_Stop_All_Legs);
	Set(Legs + 4, Full_Stop_All_Legs, Full_Stop_All_Legs, Full_Stop_All_Legs);
	Set(Legs + 5, Full_Stop_All_Legs, Full_Stop_All_Legs, Full_Stop_All_Legs);

	StepSize = ItemsOf(Full_Stop_All_Legs);

	Count++;
	if (Count >= 1)
	{
		Count = 0;
		WalkManager = Init_Work;
	}
}
*/

void Step()
{
	if (StepIndex == 0)
	{
		WalkManager();
	}

	/*for(int i = 0; i < 6; i++)
	{
		Legs[i].H1 = Leg[i].H1[StepIndex];
		Legs[i].V2 = Leg[i].V2[StepIndex];
		Legs[i].V3 = Leg[i].V3[StepIndex];
	}*/
	Legs[LEG_L1].H1 = (uint32_t)Leg[0].H1[StepIndex];
	Legs[LEG_L1].V2 = (uint32_t)Leg[0].V2[StepIndex];
	Legs[LEG_L1].V3 = (uint32_t)Leg[0].V3[StepIndex];

	Legs[LEG_R1].H1 = (uint32_t)Leg[1].H1[StepIndex];
	Legs[LEG_R1].V2 = (uint32_t)Leg[1].V2[StepIndex];
	Legs[LEG_R1].V3 = (uint32_t)Leg[1].V3[StepIndex];

	Legs[LEG_L2].H1 = (uint32_t)Leg[2].H1[StepIndex];
	Legs[LEG_L2].V2 = (uint32_t)Leg[2].V2[StepIndex];
	Legs[LEG_L2].V3 = (uint32_t)Leg[2].V3[StepIndex];

	Legs[LEG_R2].H1 = (uint32_t)Leg[3].H1[StepIndex];
	Legs[LEG_R2].V2 = (uint32_t)Leg[3].V2[StepIndex];
	Legs[LEG_R2].V3 = (uint32_t)Leg[3].V3[StepIndex];

	Legs[LEG_L3].H1 = (uint32_t)Leg[4].H1[StepIndex];
	Legs[LEG_L3].V2 = (uint32_t)Leg[4].V2[StepIndex];
	Legs[LEG_L3].V3 = (uint32_t)Leg[4].V3[StepIndex];

	Legs[LEG_R3].H1 = (uint32_t)Leg[5].H1[StepIndex];
	Legs[LEG_R3].V2 = (uint32_t)Leg[5].V2[StepIndex];
	Legs[LEG_R3].V3 = (uint32_t)Leg[5].V3[StepIndex];

	StepIndex++;
	if(StepIndex >= StepSize) StepIndex = 0;
}

/*
íàïðàâëåíèå äâèæåíèÿ

êîä  -  çíà÷åíèå
 0 		VK_LEFT
 1 		VK_UP
 2 		VK_RIGHT
 3 		VK_DOWN
 4 		VK_SHIFT
 5 		VK_CONTROL

òèïû ïîõîäîê
êîä  -  çíà÷åíèå
 6 		VK_F1
 7 		VK_F2
 8 		VK_F3

*/
//}
