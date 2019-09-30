from BaseballElimination import BaseballElimination

def main():
    filename  = input("Enter file: ")
    division = BaseballElimination(filename)
    for team in division.teams():
        if (division.isEliminated(team)):
            print(team,"is eliminated by the subset R = {",end="")
            for t in division.certificateOfElimination(team):
                print(t,end=" ")
            print("}")
        else:
            print(team,"is not eliminated")

if __name__ == "__main__":
    main()
