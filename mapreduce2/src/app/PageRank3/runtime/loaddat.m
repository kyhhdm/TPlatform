%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
%% [U,P] = loaddat(fname,ftype)
%% loads .dat file formatted like 
%%    ftype = 1 : hollins.dat, mathworks.dat
%%          = 2 : stanford.dat, stanberk.dat
%%          = 3 : .dat files from Langville (linktiny10, linkjordan, etc)
%% returns sparse transition matrix with P(i,j) = prob(i ==> j)
%% U contains the urls when ftype = 1
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [U,P] = loaddat(fname,ftype)

tic;
f = fopen(fname,'r');
U = cell(0,0);

if (ftype == 1)
  n = fscanf(f,'%d',1);
  nlink = fscanf(f,'%d',1);

  U = cell(n,1);
  ij = zeros(nlink,2);

  for i=1:n
    a = fscanf(f,'%d',1);
    s = fscanf(f,'%s',1);
    U{i} = s;
  end

  for i=1:nlink
    ij(i,1) = fscanf(f,'%d',1);
    ij(i,2) = fscanf(f,'%d',1);
  end

  P = (sparse(ij(:,1),ij(:,2),1,n,n) ~= 0);   %% 0-1 matrix
elseif (ftype == 2)
  P = spconvert(load(fname));
  n = max(size(P)); P(n,n) = 0;      % make the matrix square
elseif (ftype == 3)
  j = fscanf(f,'%s',7);
  n = fscanf(f,'%i',1);
  j = fscanf(f,'%s',5);
  P = sparse(n,n);

  for i=1:n
    j = fscanf(f,'%s',7);
    j = fscanf(f,'%i',1);
    if j >= 1
      for m=1:j
        k = fscanf(f,'%i',1);
        P(i,k+1) = 1/j;            % adjusts indexing to start at 1 instead of 0
      end
    end
  end
end

%% normalize 

P = P';        % much faster if working with columns

for i=1:n
  k = sum(P(:,i));
  if (k ~= 0)
    P(:,i) = P(:,i) / k;
  end
end

%% record indices of zero rows (not returned)
zr = find(sum(P,1) == 0);

P = P';        % flip back so row sum is one

fprintf(1,'matrix size = %d, nnz = %d, zero cols = %d\n',n,nnz(P),length(zr));
fprintf(1,'  took %f seconds\n',toc);

