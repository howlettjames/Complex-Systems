close all;

data = csvread('/home/james/Documents/ESCOM_SEMESTRE_8/3CM5_CST/GOL_Attractor/data.dat');
uniqueEdgeList = unique(sort(data,2),'rows');
uniqueEdgeList;
s=uniqueEdgeList(:,1); % reading its first column
dim = size(s,1);
s2 = transpose(s);
t=uniqueEdgeList(:,2); % reading its second column of csv file
t2 = transpose(t);
%s2 = [1 1 1 1 1 6 6 6 6 6];
%t2 = [2 3 4 5 6 7 8 9 10 11];

G = graph(s2,t2);

%remove all nodes that don't have connection
tam = numnodes(G);
id = 1;
while id <= tam
   if(size(neighbors(G,id),1)==0)
       G = rmnode(G,id);
       tam = numnodes(G);
   else
       id = id + 1;
   end
end

%showing graph

plot(G,'Layout','force');

%opening a saved graphic
%openfig('C:\Users\Juan Manuel\Desktop\Diffusion4x4.fig');