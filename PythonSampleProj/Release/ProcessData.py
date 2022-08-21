#===================================================
# Author: Shawn Way
# Date: 08/13/2022
#
# Purpose: Python coded modules for calculation,
#          return, and/or display of purchase data
#===================================================

import re
import string

FILE_STRING = 'Purchase_Item_List.txt'

# Read in purchase list
def readPurchaseList():
    purchaseList = []

    with open(FILE_STRING, 'r') as textFile:
        purchaseList = textFile.read().splitlines()

    return purchaseList

# Make a dictionary containing item names and purchase quantity
def buildPurchaseDict():
    purchaseList = readPurchaseList()
    purchaseDict = {}

    for item in purchaseList:
        if item in purchaseDict:
            purchaseDict[item] += 1
        else:
            purchaseDict[item] = 1

    return purchaseDict

# Display all items purchased today and their quantity purchased
def todayPurchaseList():
    purchaseDict = buildPurchaseDict()

    print('\nPurchase List:')

    for item in purchaseDict.items():
        print("{}: {}".format(item[0], item[1]))

    print()

# Find and display quantity purchased of a single item
def findItemPurchaseAmount(itemName):
    itemName = itemName.title()
    purchaseDict = buildPurchaseDict()

    if itemName in purchaseDict:
        return purchaseDict[itemName]
    else:
        return 0

# Display all purchased items as a histogram
def displayHistogram():
    purchaseDict = buildPurchaseDict()

    for item in purchaseDict.items():
        print("{}{}".format(item[0], '*' * item[1]))

# Print purchase list for testing
def printsomething():
    purchaseDict = buildPurchaseDict()
    print(purchaseDict)