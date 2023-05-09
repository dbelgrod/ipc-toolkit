
#include <ipc/broad_phase/broadmark_util.hpp>
#include <ipc/broad_phase/sweep_and_tiniest_queue.hpp>
#include "Broadphase/Algorithms/GPU/Bullet3GPUAlgorithms.h"
#include "Broadphase/Algorithms/BF/BF.h"
#include "Broadphase/Algorithms/DBVT/DBVT.h"
#include "Broadphase/Algorithms/Grid/Grid_ND.h"
#include "Broadphase/Algorithms/Grid/Grid_ND_Parallel.h"
#include "Broadphase/Algorithms/Grid/Grid_ND_SAP.h"
#include "Broadphase/Algorithms/KD/KD.h"
#include "Broadphase/Algorithms/SAP/SAP.h"
#include "Broadphase/Algorithms/SAP/SAP_Parallel.h"
#include "Broadphase/Algorithms/SAP/SAP_SIMD_Parallel.h"
#include "Broadphase/Algorithms/Tracy/Tracy.h"
#include "Broadphase/Algorithms/Tracy/Tracy_Parallel.h"
#include "Broadphase/Algorithms/iSAP/AxisSweep.h"
// #include "Broadphase/Algorithms/CGAL/CGAL.h"

namespace ipc {

template <class T> class Broadmark : public CopyMeshBroadPhase {
public:
    Broadmark() : interface() { }
    /// @brief Build the broad phase for static collision detection.
    /// @param vertices Vertex positions
    /// @param edges Collision mesh edges
    /// @param faces Collision mesh faces
    /// @param inflation_radius Radius of inflation around all elements.
    void build(
        const Eigen::MatrixXd& vertices,
        const Eigen::MatrixXi& edges,
        const Eigen::MatrixXi& faces,
        double inflation_radius = 0) override;

    /// @brief Build the broad phase for continuous collision detection.
    /// @param vertices_t0 Starting vertex positions
    /// @param vertices_t1 Ending vertex positions
    /// @param edges Collision mesh edges
    /// @param faces Collision mesh faces
    /// @param inflation_radius Radius of inflation around all elements.
    void build(
        const Eigen::MatrixXd& vertices_t0,
        const Eigen::MatrixXd& vertices_t1,
        const Eigen::MatrixXi& edges,
        const Eigen::MatrixXi& faces,
        double inflation_radius = 0) override;

    /// @brief Clear any built data.
    void clear() override;

    /// @brief Find the candidate edge-vertex collisisons.
    /// @param[out] candidates The candidate edge-vertex collisisons.
    void detect_edge_vertex_candidates(
        std::vector<EdgeVertexCandidate>& candidates) const override;

    /// @brief Find the candidate edge-edge collisions.
    /// @param[out] candidates The candidate edge-edge collisisons.
    void detect_edge_edge_candidates(
        std::vector<EdgeEdgeCandidate>& candidates) const override;

    /// @brief Find the candidate face-vertex collisions.
    /// @param[out] candidates The candidate face-vertex collisisons.
    void detect_face_vertex_candidates(
        std::vector<FaceVertexCandidate>& candidates) const override;

    /// @brief Find the candidate edge-face intersections.
    /// @param[out] candidates The candidate edge-face intersections.
    void detect_edge_face_candidates(
        std::vector<EdgeFaceCandidate>& candidates) const override;

    /// @brief Detect all collision candidates needed for a given dimensional simulation.
    /// @param dim The dimension of the simulation (i.e., 2 or 3).
    /// @param candidates The detected collision candidates.
    void detect_collision_candidates(int dim, Candidates& candidates) const;

protected:
    long to_edge_id(long id) const;
    long to_face_id(long id) const;

    bool is_vertex(long id) const;
    bool is_edge(long id) const;
    bool is_face(long id) const;

    std::vector<broadmark::Aabb> boxes;
    std::vector<std::pair<int, int>> overlaps;
    ipc::Interface<T> interface;
    long num_vertices;
    // std::vector<ipc::AABB> vertex_boxes;
    // std::vector<ipc::AABB> edge_boxes;
    // std::vector<ipc::AABB> face_boxes;
};

} // namespace ipc