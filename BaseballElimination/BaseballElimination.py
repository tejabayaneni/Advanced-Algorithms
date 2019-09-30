from FordFulkerson import FordFulkerson
from FlowNetwork import FlowNetwork
from FlowEdge import FlowEdge
inf=1000000000000
class BaseballElimination:

    def __init__(self,filename):
        self.inFile = open(filename)
        self.teammap={}
    def numberOfTeams(self):
        self.inFile.seek(0) #to get the file pointer to the first position , after reading the end of file
        noOfTeams=self.inFile.readline() #reading first line of the file.
        return noOfTeams

    def teams(self):
        self.numberOfTeams()#to get the number of teams and read from the next line
        self.teamslist=[] #created a list to add all team names
        lines=self.inFile.readlines() # reading all lines
        for line in lines:
            team=line.split(None,1)[0] #getting the first line
            value=' '.join(line.split()[1:])
            self.teamslist.append(line.split(None,1)[0])# adding teams to a list
            self.teammap[team]=value #adding teams and their values to a map
        return self.teamslist

    def wins(self, team):
        for teams in self.teammap:
            if teams==team:
                val=self.teammap[teams]
                winchar=val.split(' ',1)[0] #reading the first value to get the wins
                win=int(winchar)
        return win

#reading the value of the team from the map and getting the losses
    def losses(self, team):
        for teams in self.teammap:
            if teams==team:
                val=self.teammap[teams]
                a=val.split(' ')
                losechar=a[1]
                lose=int(losechar)
            # else:
            #     print("No team found")
            #return 0
        #print("lose",lose)
        return lose

#reading the value of the team from the map and getting the remaining

    def remaining(self, team):
        for teams in self.teammap:
            #print(teams,team)
            if teams==team:
                val=self.teammap[teams]
                rem=val.split(' ')
                remainingchar=rem[2]
                remaining=int(remainingchar)
            # else:
            #     print("No team found")
            #return 0
        #print("remaining",remaining)
        return remaining

#reading the value of the team from the map and getting the against

    def against(self, team1, team2):
        #print(team1,team2)
        index1=self.teamslist.index(team1)
        index2=self.teamslist.index(team2)
        teamvalue=self.teammap[team1]
        #print(teamvalue)
        remt1t2char=teamvalue.split(' ')[index2+3]
        remt1t2=int(remt1t2char)
        return remt1t2
#calculating the trivial solution
    def trivial(self,team):
        teams = self.teams()
        self.winningteams=[] #trivial elimination list
        self.otherteams=[]# to add the other teams except team which we are checking
        index=self.teamslist.index(team)
        for current_team in teams:
            if current_team !=team:
                self.otherteams.append(current_team)
#checking trivial case
        #print("teams",teams)
        for current_team in teams:
            if(self.wins(team)+self.remaining(team)<self.wins(current_team)):
                self.winningteams.append(current_team) #adding teams to the list
#checking whether the team is eliminated or not
        if(len(self.winningteams)>0):
            return True
        else:
            return False
    def isEliminated(self, team):
        check=self.trivial(team) #to check whether the team is eliminated by trivial case or not
        if(check):
            return self.winningteams
        else:
            n=len(self.otherteams) #get the length of the list
            graphmap={} #initializing map for all vertices
            pos=1
            s=0
            graphmap[s]=0 #s taking s as 0
            #taking each vertex pairs and mapped
            for i in range (n):
                for j in range(i,n):
                    if i!=j:
                        graphvertices=(self.otherteams[i],self.otherteams[j])
                        graphmap[graphvertices]=pos
                        pos=pos+1
            temp=pos #taking this value to cut the game vertices
            #adding the team names to the map
            for i in range(n):
                graphmap[self.otherteams[i]]=pos
                pos=pos+1
            graphmap[pos]=pos #adding t value as the final one to the map
            num=int((n*(n-1))/2)
            v=len(graphmap)# length of the vertices to
            G=FlowNetwork(v)
            t = G.V()-1
            totalwin=self.wins(team)+self.remaining(team) #total wins a team can win
#adding the game vertices to the graph
            for i in range (n):
                for j in range(i,n):
                    if i!=j:
                        #print(i,j,n)
                        a=self.otherteams[i]
                        b=self.otherteams[j]
                        rem=self.against(a,b)
                        pair=(a,b)
                        vertex=graphmap[pair]
                        G.addEdge(FlowEdge(graphmap[s],vertex,rem))
                        G.addEdge(FlowEdge(vertex,graphmap[a],inf))
                        G.addEdge(FlowEdge(vertex,graphmap[b],inf))
            #print(G)
            #adding team vertices to graph
            for i in range(n):
                a=self.otherteams[i]
                win=self.wins(a)
                tot=totalwin-win
                G.addEdge(FlowEdge(graphmap[a],graphmap[pos],tot))

            #print(G)
            maxflow = FordFulkerson(G, s, t)
            #print("Max flow from",s,"to",t)

            for v in range(G.V()):
                for e in G.adj(v):
                    if ((v == e.From()) and e.flow() > 0):
                        pass
                        #print(" ",e)
            cut = []
            for v in range(temp,G.V()):
                if (maxflow.inCut(v)):
                    cut.append(v)
            #print(graphmap)
            #print("Min cut:",cut)
            #print("Max flow value =",maxflow.value())
            self.subset=[]
            if(len(cut)>0):
                for cutval in cut:
                    for key,val in graphmap.items():
                        if cutval==val:
                            #print(key)
                            self.subset.append(key)
                return self.subset
            else:
                return False

    def certificateOfElimination(self, team):
        flag1=self.trivial(team)#checking whether team is eliminated by trivial
        if(flag1):
            return self.winningteams #returning trivial subset
        else:
            flag2=self.isEliminated(team)
            if(flag2):
                return self.subset
            else:
                return None
