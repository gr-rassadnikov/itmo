package search;

public class BinarySearch {
    //Pred: a-sort(from bigger to smaller) && a[-1]=INF && a[a.length]=-INF
    public static int it(int x, int[] a) {
        //a-sort && a[-1]=INF && a[a.length]=-INF
        int l = -1;
        int r = a.length;
        //l==-1 && r==a.length && a-sort  && a[-1]=INF && a[a.length]=-INF ===>
        // a[r]<=x && a[l]>x && l<r
        //INV START: a[r]<=x && a[l]>x && l<r
        while (l < r - 1) {
            // a[r]<=x && a[l]>x&& l<r-1     && (r-l)уменьшается      ---
            int m = (l + r) / 2;
            //a[r]<=x && a[l]>x && m = (l + r) / 2 && l<r-1
            if (a[m] > x) {
                //a[r]<=x && a[l]>x && m = (l + r) / 2 && a[m]>x ===>
                //a[r]<=x && m = (l + r) / 2 && a[m]>x && l<m<r
                l = m;
                // a[r]<=x && a[l]>x && l<r-1 && (r-l)уменьшилось
            } else {
                //a[r]<=x && a[l]>x && m = (l + r) / 2 && a[m]<=x
                //a[l]>x && m = (l + r) / 2 && a[m]<=x && l<m<r
                r = m;
                // a[r]<=x && a[l]>x && l<r-1 && (r-l)уменьшилось
            }
            // a[r]<=x && a[l]>x && l<r-1   && (r-l)уменьшается
        }
        //INV END l>=r-1 && a[r]<=x && a[l]>x && l<r ===>
        //        l=r-1 && a[r]<=x && a[l]>x         ===>
        //        a[r]<=x && a[r-1]>x

        return r;
    }
    //Post: a[r]<=x && a[r-1]>x
    //D: (r-l)уменьшается на каждой итерации цикла ==>l >= r - 1 ==> закончится


    // :NOTE: pre-condition too strict
    //Pred: a-sort(from bigger to smaller) && a[l]>x>=a[r] && -1<=l<r<=a.length && a[-1]=INF && a[a.length]=-INF
    public static int rec(int x, int[] a, int l, int r) {
        //-1<=l<r<=a.length && a[l]>=a[r] && a-sort
        if (l >= r - 1) {
            // -1<=l<r<=a.length && l >= r - 1 && a[l]>x>=a[r] &&a-sort
            //===> l=r-1 && a[l]>x>=a[r] && a-sort
            //===> a[r]<=x && a[r-1]>x
            return r;
        } else {
            //-1<=l<r<=a.length && a[l]>=a[r] && l<r-1 && a-sort
        }
        //-1<=l<r<=a.length && a[l]>=a[r] && l<r-1 && a-sort
        int m = (l + r) / 2;
        //-1<=l<r<=a.length && a[l]>=a[r] && l<r-1 && m = (l + r) / 2 && a-sort   ===>
        //1<=l<m<=r-1<r<=a.length && a[l]>=a[m]>=a[r] && a-sort

        if (a[m] > x) {
            //a-sort && a[m]>x>=a[r] && -1<m<r<=a.length
            l = m;
            //a-sort && a[m]>x>=a[r] && -1<m<r<=a.length && l=m
            //a-sort && a[l]>x>=a[r] && -1<=l<r<=a.length && a[-1]=INF && a[a.length]=-INF
            return rec(x, a, l, r); //a[r]<=x && a[r-1]>x
        } else {
            // a-sort && a[l]>x>=a[m] && -1<=l<m<a.length
            r = m;
            // a-sort && a[l]>x>=a[m] && -1<=l<m<a.length && r=m
            // a-sort && a[l]>x>=a[r] && -1<=l<r<a.length && a[-1]=INF && a[a.length]=-INF
            return rec(x, a, l, r);//a[r]<=x && a[r-1]>x
        }
        //a[r]<=x && a[r-1]>x
    }
    //Post: a[r]<=x && a[r-1]>x
    //D: l<r, m=(r+l)/2 ==> (r-l) делят на 2 ==> (r-l)<=1 === l>=r-1 ==> закончится


    // :NOTE: too informal notation
    //Pred: INPUT: String(that java can convert to int) args[0], args[1]...args[n]
    //&& args[1...n]-sort(from bigger to smaller)

    //Post: OUTPUT: min i, that args[i]<=args[0]
    public static void main(String[] args) {
        int x = Integer.parseInt(args[0]);
        int[] a = new int[args.length - 1];
        for (int i = 0; i < a.length; i++) {
            a[i] = Integer.parseInt(args[i + 1]);
        }
        //System.out.println(rec(x, a, -1, a.length));
        // :NOTE: only one method is tested
        System.out.println(it(x, a));
    }
}
