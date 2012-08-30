% generate link .dat file from webbot log
% before running:
%    remove all \tab and \# from input file
%    take care of index.htm defaults
function link2dat(fname,ofname)

murl = 10000;         
m404 = 1000;      
mlink = 10*murl;

U = cell(murl,1);
hash = zeros(murl,1);
U404 = cell(m404,1);
hash404 = zeros(m404,1);
ii = zeros(mlink,1);
ij = zeros(mlink,1);

f = fopen(fname,'r');

nurl = 0;
n404 = 0;
nlink = 0;

while (1)
  is404 = 1;
  [src,count] = fscanf(f,'%s',1);
  if (count == 0)
    break;
  end
  if (isequal(src,'::::'))
    is404 = 0;
    src = fscanf(f,'%s',1);
  end
  dest = fscanf(f,'%s',1);
  if (~isequal(dest,'->'))
    disp(['error' src])
  end
  dest = fscanf(f,'%s',1);

  % remember missing pages so we can throw away broken links
  if (is404)
    n404 = n404 + 1;
    U404{n404} = dest;
    hash404(n404) = hashfun(dest);
    continue;
  end

  q = 0;
  x = hashfun(dest);
  for k = find(hash404(1:n404) == x)'
    if isequal(U404{k},dest)
      q = k;
      break
    end
  end
  if (q > 0)    % broken link
    continue;
  end

  p = 0;
  x = hashfun(src);
  for k = find(hash(1:nurl) == x)' 
    if isequal(U{k},src)
      p = k;
      break
    end
  end
  if (p == 0)           % new URL found
    nurl = nurl + 1;
    U{nurl} = src;
    if (src(length(src)) == '/')
      disp(['default url? ' src ' -> ' dest])
    end
    hash(nurl) = x;
    p = nurl;
  end

  q = 0;
  x = hashfun(dest);
  for k = find(hash(1:nurl) == x)'
    if isequal(U{k},dest)
      q = k;
      break
    end
  end
  if (q == 0)          % new URL found
    nurl = nurl + 1;
    U{nurl} = dest;
    if (dest(length(dest)) == '/')
      disp(['default url? ' src ' -> ' dest])
    end
    hash(nurl) = x;
    q = nurl;
  end

  if ((p > 0) & (q > 0) & (p ~= q))        % don't count self-links
    nlink = nlink + 1;
    ii(nlink) = p;
    ij(nlink) = q;
  end

end

U = U(1:nurl);
ii = ii(1:nlink);
ij = ij(1:nlink);
fclose(f);


P = (sparse(ii,ij,1,nurl,nurl) ~= 0);      % eliminates duplicates
[nurl nlink nnz(P) n404]

f = fopen(ofname,'w');
fprintf(f, '%d %d\n', nurl, nnz(P));
for i=1:nurl
  fprintf(f, '%d %s \n', i, U{i});
end
[a,b] = find(P);
for i=1:length(a)
  fprintf(f,'%d %d\n',a(i),b(i));
end
fclose(f);

return

% almost unique numeric hash code
function h = hashfun(url)
h = length(url) + 1024*sum(url);
return


