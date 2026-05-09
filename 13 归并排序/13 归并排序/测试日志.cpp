//#include <iostream>
//using namespace std;
//
//// 辅助函数：打印数组，标记当前处理的区间 [l, r]
//void PrintArray(int arr[], int size, int l = -1, int r = -1) {
//    for (int i = 0; i < size; i++) {
//        if (i >= l && i <= r) {
//            // 用[]标记当前正在处理的区间
//            cout << "[" << arr[i] << "] ";
//        }
//        else {
//            cout << arr[i] << " ";
//        }
//    }
//    cout << endl;
//}
//
//// 归并排序（带调试打印）
//void MergeSort(int arr[], int l, int r, int size) {
//    // 1. 递归结束条件
//    if (l >= r) {
//        if (l == r) {
//            cout << "  ↳ 递归终止：区间 [" << l << "," << r << "] 只有1个元素，无需排序\n";
//        }
//        return;
//    }
//
//    // 打印当前进入的递归区间
//    cout << "\n===== 进入 MergeSort(arr, " << l << ", " << r << ") =====\n";
//    cout << "当前数组状态：";
//    PrintArray(arr, size, l, r);
//
//    // 2. 递的过程：分割区间
//    int mid = (l + r) / 2;
//    cout << "分割区间：[" << l << "," << r << "] → 左半[" << l << "," << mid << "] 右半[" << mid + 1 << "," << r << "]\n";
//
//    // 递归处理左右子区间
//    MergeSort(arr, l, mid, size);
//    MergeSort(arr, mid + 1, r, size);
//
//    // 3. 归并的过程：合并两个有序子序列
//    cout << "\n--- 开始合并区间 [" << l << "," << r << "] ---\n";
//    cout << "合并前，左半[" << l << "," << mid << "]：";
//    for (int i = l; i <= mid; i++) cout << arr[i] << " ";
//    cout << "\n合并前，右半[" << mid + 1 << "," << r << "]：";
//    for (int i = mid + 1; i <= r; i++) cout << arr[i] << " ";
//    cout << endl;
//
//    // 开辟临时数组，存放合并结果（大小刚好是当前区间的长度）
//    int* p = new int[r - l + 1];
//    int idx = 0;
//    int i = l;    // 左半区间的指针
//    int j = mid + 1; // 右半区间的指针
//
//    // 双指针合并两个有序序列（保持稳定的关键：<= 取左边）
//    while (i <= mid && j <= r) {
//        if (arr[i] > arr[j]) {
//            p[idx++] = arr[j++];
//        }
//        else {
//            p[idx++] = arr[i++];
//        }
//    }
//    // 把左半剩余元素放入临时数组
//    while (i <= mid) {
//        p[idx++] = arr[i++];
//    }
//    // 把右半剩余元素放入临时数组
//    while (j <= r) {
//        p[idx++] = arr[j++];
//    }
//
//    // 打印合并后的临时数组
//    cout << "合并完成，临时数组p的内容：";
//    for (int k = 0; k < r - l + 1; k++) {
//        cout << p[k] << " ";
//    }
//    cout << endl;
//
//    // 4. 把临时数组的结果拷贝回原数组的 [l, r] 区间
//    cout << "【关键拷贝步骤】从原数组下标 " << l << " 开始，拷贝临时数组到 [" << l << "," << r << "] 区间\n";
//    cout << "拷贝前的原数组：";
//    PrintArray(arr, size, l, r);
//
//    // 这里就是你问的循环：必须从 i=l 开始，不能从0开始！
//    for (i = l, j = 0; i <= r; i++, j++) {
//        arr[i] = p[j];
//    }
//
//    cout << "拷贝后的原数组：";
//    PrintArray(arr, size, l, r);
//
//    // 释放临时数组
//    delete[] p;
//    cout << "--- 区间 [" << l << "," << r << "] 合并完成，已排序 ---\n";
//}
//
//int main() {
//    // 用你画的例子数组测试
//    int arr[] = { 62, 99, 38, 75, 81, 40, 51, 60, 14, 36 };
//    int size = sizeof(arr) / sizeof(arr[0]);
//
//    cout << "===== 初始数组：";
//    PrintArray(arr, size);
//    cout << "=====================================\n";
//
//    MergeSort(arr, 0, size - 1, size);
//
//    cout << "\n===== 最终排序结果：";
//    PrintArray(arr, size);
//    return 0;
//}