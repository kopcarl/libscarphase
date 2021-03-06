/**
 * Copyright (c) 2011-2013 Andreas Sembrant
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of the copyright holders nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Andreas Sembrant
 *
 */

#ifndef __SCARPHASE_INTERNAL_CLASSIFIER_BOUNDED_LF_CLASSIFIER_HPP
#define __SCARPHASE_INTERNAL_CLASSIFIER_BOUNDED_LF_CLASSIFIER_HPP

#include <stdint.h>

#include <boost/array.hpp>
#include <scarphase/internal/classifier/leader_follower_classifier.hpp>

/**
 * Bounded LF has a finite number of cluster to lower the overhead.
 * If the number of phases if above NO_CLUSTERS, it will start to forget
 * the older clusters, i.e., the same phase might have two different phase ids.
 */
#define NO_CLUSTERS 64

namespace scarphase {
namespace internal {
namespace classifier {

/**
 * @brief
 */
class BoundedLeaderFollowerClassifier //--------------------------------------//
    : public virtual LeaderFollowerClassifier
{

public: //--------------------------------------------------------------------//

    /**
     * @brief C-tor
     */
    BoundedLeaderFollowerClassifier(double similarity_threshold,
                                    unsigned int transition_threshold);

    /**
     * @brief D-tor
     */
    virtual ~BoundedLeaderFollowerClassifier();

    /**
     * @see scarphase::classifier.
     */
    virtual int
    ClassifySignature(const spi::util::Signature& signature);

    /**
     * @see scarphase::classifier.
     */
    virtual int
    FindPhase(const spi::util::Signature &signature, double threshold);

protected: //-----------------------------------------------------------------//

    /**
     * @brief
     */
    struct Cluster : LeaderFollowerClassifier::Cluster
    {

        /**
         * @brief C-tor
         */
        Cluster();

        /**
         * @brief The age of the entry.
         */
        unsigned int age;

    };

    /**
     * @brief The age.
     */
    unsigned int next_age;

    /**
     * @brief Table with all the means, etc.
     */
    boost::array<Cluster, NO_CLUSTERS> clusters;

};

} /* namespace classifier */
} /* namespace internal */
} /* namespace scarphase */


#endif /* __SCARPHASE_INTERNAL_CLASSIFIER_BOUNDED_LF_CLASSIFIER_HPP */
