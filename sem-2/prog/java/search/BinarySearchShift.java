package search;

public class BinarySearchShift {
    // :NOTE: empty case is invalid
    // :NOTE: iteration over strings
    //Pred: x=a[0] && a-sort(from smaller to bigger,from smaller to bigger ) && a[-1]=a[0] && a[a.length]=a[a.length-1]
    public static int it(int x, String[] a) {
        //a-sort && a[-1]=a[0] && a[a.length]=a[a.length-1]
        int l = -1;
        int r = a.length;
        //l==-1 && r==a.length && a-sort  && a[-1]=a[0] && a[a.length]=a[a.length-1] ===>
        // a[r]<x && a[l]=x && l<r
        //INV START: a[r]<x && a[l]>=x && l<r
        while (l < r - 1) {
            // a[r]<x && a[l]>=x&& l<r-1     && (r-l)уменьшается      ---
            int m = (l + r) / 2;
            //a[r]<x && a[l]>=x && m = (l + r) / 2 && l<r-1
            if (Integer.parseInt(a[m]) >= x) {
                //a[r]<x && a[l]>=x && m = (l + r) / 2 && a[m]>=x ===>
                //a[r]<x && m = (l + r) / 2 && a[m]>=x && l<m<r
                l = m;
                // a[r]<x && a[l]>=x && l<r-1 && (r-l)уменьшилось
            } else {
                //a[r]<x && a[l]=>x && m = (l + r) / 2 && a[m]<x
                //a[l]>=x && m = (l + r) / 2 && a[m]<x && l<m<r
                r = m;
                // a[r]<x && a[l]>=x && l<r-1 && (r-l)уменьшилось
            }
            // a[r]<x && a[l]>=x && l<r-1   && (r-l)уменьшается
        }
        //INV END l>=r-1 && a[r]<x && a[l]=>x && l<r ===>
        //        l=r-1 && a[r]<x && a[l]>=x         ===>
        //        a[r]<x && a[r-1]>=x
        if (r == a.length) {
            return 0;
        }

        return r;
    }
    // :NOTE: proof informal
    //Post: a[r]<x && a[r-1]>=x
    //D: (r-l)уменьшается на каждой итерации цикла ==>l >= r - 1 ==> закончится


    //Pred: a-sort(from smaller to bigger,from smaller to bigger)
    // && a[l]>=x>a[r] && -1<=l<r<=a.length && a[-1]=a[0] && a[a.length]=a[a.length-1]
    public static int rec(int x, String[] a, int l, int r) {
        //-1<=l<r<=a.length && a[l]>=x>a[r] && a-sort
        if (l >= r - 1) {
            // -1<=l<r<=a.length && l >= r - 1 && a[l]>=x>a[r] &&a-sort
            //===> l=r-1 && a[l]>=x>a[r] && a-sort
            //===> a[r]<x && a[r-1]>=x
            if (r == a.length) {
                return 0;
            }
            return r;
        } else {
            //-1<=l<r<=a.length && a[l]>=x>a[r] && l<r-1 && a-sort
        }
        //-1<=l<r<=a.length && a[l]>=x>a[r] && l<r-1 && a-sort
        int m = (l + r) / 2;
        //-1<=l<r<=a.length && a[l]>=x>a[r] && l<r-1 && m = (l + r) / 2 && a-sort   ===>
        //1<=l<m<=r-1<r<=a.length && a[l]>=a[m]>a[r] && a-sort

        if (Integer.parseInt(a[m]) >= x) {
            //a-sort && a[m]>=x>a[r] && -1<m<r<=a.length
            l = m;
            //a-sort && a[m]>=x>a[r] && -1<m<r<=a.length && l=m
            //a-sort && a[l]>=x>=a[r] && -1<=l<r<=a.length &&
            return rec(x, a, l, r); //a[r]<=x && a[r-1]>x
        } else {
            // a-sort && a[l]>=x>a[m] && -1<=l<m<a.length
            r = m;
            // a-sort && a[l]>=x>a[m] && -1<=l<m<a.length && r=m
            // a-sort && a[l]>=x>a[r] && -1<=l<r<a.length
            return rec(x, a, l, r);//a[r]<=x && a[r-1]>x
        }
        //a[r]<x && a[r-1]>=x
    }
    //Post: a[r]<x && a[r-1]>=x
    //D: l<r, m=(r+l)/2 ==> (r-l) делят на 2 ==> (r-l)<=1 === l>=r-1 ==> закончится


    //Pred: INPUT: String(that java can convert to int) args[0],args[1]...args[n]
    //&& args[0...n]-sort(from smaller to bigger,from smaller to bigger)

    //Post: OUTPUT: k, that args[k]-наименьшее
    public static void main(String[] args) {
        System.out.println(it(Integer.parseInt(args[0]), args));
        //System.out.println(it(Integer.parseInt(args[0]), args));
    }
}
