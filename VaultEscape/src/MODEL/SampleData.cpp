#include "model/SampleData.h"
#include <algorithm>

namespace vh::sample {

// ------------------------------------------------------------------ trees

std::unique_ptr<BinaryTree> binaryTree() {
    auto t = std::make_unique<BinaryTree>();
    TreeNode* r = t->setRoot(5);
    TreeNode* a = t->addLeft(r, 12);
    TreeNode* b = t->addRight(r, 7);
    t->addLeft(a, 3);
    t->addRight(a, 9);
    t->addLeft(b, 4);
    t->addRight(b, 8);
    return t;
}

// Builds shape  k0 / (k1 / (k3, k4)) (k2 / (k5, k6))  on any BST-derived tree and returns the root.
static BSTNode* buildSevenNodeShape(BST& t, const int k[7]) {
    BSTNode* n[7];
    for (int i = 0; i < 7; ++i) n[i] = t.createNode(k[i]);
    linkChild(n[0], n[1], Side::LEFT);
    linkChild(n[0], n[2], Side::RIGHT);
    linkChild(n[1], n[3], Side::LEFT);
    linkChild(n[1], n[4], Side::RIGHT);
    linkChild(n[2], n[5], Side::LEFT);
    linkChild(n[2], n[6], Side::RIGHT);
    return n[0];
}

static void fillAvlMetadata(AVLNode* n) {
    if (!n) return;
    AVLNode* l = static_cast<AVLNode*>(n->left);
    AVLNode* r = static_cast<AVLNode*>(n->right);
    fillAvlMetadata(l);
    fillAvlMetadata(r);
    n->height = 1 + std::max(l ? l->height : 0, r ? r->height : 0);
    n->size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
}

std::unique_ptr<BST> bst() {
    auto t = std::make_unique<BST>();
    const int k[7] = {50, 30, 70, 20, 40, 60, 80};
    t->adoptRoot(buildSevenNodeShape(*t, k));
    return t;
}

std::unique_ptr<AVLTree> avlBalanced() {
    auto t = std::make_unique<AVLTree>();
    const int k[7] = {50, 30, 70, 20, 40, 60, 80};
    BSTNode* root = buildSevenNodeShape(*t, k);
    fillAvlMetadata(static_cast<AVLNode*>(root));
    t->adoptRoot(root);
    return t;
}

std::unique_ptr<AVLTree> avlLeftHeavy() {
    auto t = std::make_unique<AVLTree>();
    BSTNode* a = t->createNode(30);
    BSTNode* b = t->createNode(20);
    BSTNode* c = t->createNode(10);
    linkChild(a, b, Side::LEFT);
    linkChild(b, c, Side::LEFT);
    fillAvlMetadata(static_cast<AVLNode*>(a));
    t->adoptRoot(a);
    return t;
}

// ------------------------------------------------------------------ heaps

std::unique_ptr<MaxHeap> heap() {
    return std::make_unique<MaxHeap>(std::vector<int>{90, 70, 80, 40, 50, 60, 30});
}

std::unique_ptr<MaxHeap> heapWithSortedRegion() {
    auto h = std::make_unique<MaxHeap>();
    h->setState({60, 50, 30, 40, 70, 80, 90}, 4);
    return h;
}

// ------------------------------------------------------------------ event logs

static Event makeEvent(EventType type) {
    Event e;
    e.type = type;
    return e;
}

ModelEventLog bstSearchEvents() {
    auto t = bst();
    const BSTNode* n50 = t->root();
    const BSTNode* n70 = static_cast<const BSTNode*>(n50->right);
    const BSTNode* n60 = static_cast<const BSTNode*>(n70->left);

    ModelEventLog log;
    auto visit = [&](const BSTNode* n) { Event e = makeEvent(EventType::VISIT); e.nodeId = n->id; log.add(e); };
    auto compare = [&](const BSTNode* n, int key, int result) {
        Event e = makeEvent(EventType::COMPARE);
        e.nodeId = n->id; e.key = key; e.result = result;
        log.add(e);
    };
    visit(n50); compare(n50, 60, +1);
    visit(n70); compare(n70, 60, -1);
    visit(n60); compare(n60, 60, 0);
    Event done = makeEvent(EventType::DONE);
    done.text = "found 60";
    log.add(done);
    return log;
}

ModelEventLog avlRotationEvents() {
    auto t = avlLeftHeavy();
    const AVLNode* n30 = t->avlRoot();
    const AVLNode* n20 = static_cast<const AVLNode*>(n30->left);

    ModelEventLog log;
    Event alert = makeEvent(EventType::BALANCE_ALERT);
    alert.nodeId = n30->id; alert.balanceFactor = 2;
    log.add(alert);

    Event rot = makeEvent(EventType::ROTATE);
    rot.nodeId = n30->id; rot.otherId = n20->id;
    rot.rotation = RotationType::LL; rot.side = Side::RIGHT;     // LL case is fixed by a right rotation
    log.add(rot);

    Event h = makeEvent(EventType::UPDATE_HEIGHT);
    h.nodeId = n30->id; h.oldValue = 3; h.newValue = 1;
    log.add(h);
    Event h2 = makeEvent(EventType::UPDATE_HEIGHT);
    h2.nodeId = n20->id; h2.oldValue = 2; h2.newValue = 2;
    log.add(h2);
    Event s = makeEvent(EventType::UPDATE_SIZE);
    s.nodeId = n30->id; s.oldValue = 3; s.newValue = 1;
    log.add(s);
    Event s2 = makeEvent(EventType::UPDATE_SIZE);
    s2.nodeId = n20->id; s2.oldValue = 2; s2.newValue = 3;
    log.add(s2);

    Event done = makeEvent(EventType::DONE);
    done.text = "LL repaired";
    log.add(done);
    return log;
}

ModelEventLog heapExtractEvents() {
    // heap(): {90,70,80,40,50,60,30}, size 7
    ModelEventLog log;

    Event ex = makeEvent(EventType::EXTRACT_MAX);
    ex.value = 90; ex.indexA = 0; ex.heapSize = 7;
    log.add(ex);

    Event sw = makeEvent(EventType::HEAP_SWAP);
    sw.indexA = 0; sw.indexB = 6; sw.oldValue = 90; sw.newValue = 30; sw.text = "root <-> last active";
    log.add(sw);

    Event sz = makeEvent(EventType::HEAP_SIZE_CHANGE);
    sz.oldValue = 7; sz.newValue = 6;
    log.add(sz);

    Event ms = makeEvent(EventType::MARK_SORTED);
    ms.indexA = 6; ms.value = 90;
    log.add(ms);

    Event hs = makeEvent(EventType::HEAPIFY_START);
    hs.indexA = 0; hs.heapSize = 6;
    log.add(hs);

    Event s1 = makeEvent(EventType::HEAP_SWAP);               // {30,70,80,...} -> {80,70,30,...}
    s1.indexA = 0; s1.indexB = 2; s1.oldValue = 30; s1.newValue = 80; s1.text = "sift down";
    log.add(s1);
    Event s2 = makeEvent(EventType::HEAP_SWAP);               // 30 moves on to index 5 (value 60)
    s2.indexA = 2; s2.indexB = 5; s2.oldValue = 30; s2.newValue = 60; s2.text = "sift down";
    log.add(s2);

    Event hd = makeEvent(EventType::HEAPIFY_DONE);
    hd.indexA = 5; hd.heapSize = 6;
    log.add(hd);

    Event done = makeEvent(EventType::DONE);
    done.text = "extracted 90";
    log.add(done);
    return log;
}

} // namespace vh::sample
